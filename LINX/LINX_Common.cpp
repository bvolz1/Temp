#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "LINX_Common.h"

#include "device/LINX_Device.h"

unsigned long getSeconds()
{
	timespec mTime;
	clock_gettime(CLOCK_MONOTONIC, &mTime);	
	return mTime.tv_sec;
}

unsigned char computeChecksum(unsigned char* packetBuffer)
{  
  unsigned char checksum = 0;
  
  //Sum All Bytes In The Packet Except The Last (Checksum Byte)
  for(int i=0; i<(packetBuffer[1] - 1); i++)
  {
    checksum += packetBuffer[i];
  }  
  return checksum; 
}


bool checksumPassed(unsigned char* packetBuffer)
{
  return (computeChecksum(packetBuffer) == packetBuffer[packetBuffer[1]-1]);
}


void statusResponse(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer, LINXStatus status)
{
	packetize(commandPacketBuffer, responsePacketBuffer, 0, status); 
}


LINXStatus processCommand(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer, LINXDevice &LINXDev)
{
	DEBUGCMDPACKET(commandPacketBuffer);
		
	//Store Some Local Values For Convenience
	unsigned char commandLength = commandPacketBuffer[1];
	unsigned int command = commandPacketBuffer[4] << 8 | commandPacketBuffer[5];
	
	LINXStatus Lstatus = L_OK;
	
	switch(command)
	{
	
	/************************************************************************************
    * SYSTEM COMMANDS
    ************************************************************************************/
	case 0x0000: // Sync Packet        
		statusResponse(commandPacketBuffer, responsePacketBuffer, L_OK);
		break;
	 
	case 0x0003: // Get Device ID     
		responsePacketBuffer[5] = LINXDev.deviceFamily;
		responsePacketBuffer[6] = LINXDev.deviceID;    
		packetize(commandPacketBuffer, responsePacketBuffer, 2, L_OK); 
		break;	
		
	case 0x0004: //Get LINX API Version
		responsePacketBuffer[5] = LINXDev.linxAPIMajor;
		responsePacketBuffer[6] = LINXDev.linxAPIMinor;
		responsePacketBuffer[7] = LINXDev.linxAPISubminor;   
		packetize(commandPacketBuffer, responsePacketBuffer, 3, L_OK); 
		break;
		
	case 0x0008: // Get DIO Channels
		dataBufferResponse(commandPacketBuffer, responsePacketBuffer, LINXDev.DIOChans, LINXDev.numDIOChans, L_OK);
		break;
	
	case 0x0009: // Get AI Channels
        dataBufferResponse(commandPacketBuffer, responsePacketBuffer, LINXDev.AIChans, LINXDev.numAIChans, L_OK);
       break;
	   
    case 0x000A: // Get AO Channels
        dataBufferResponse(commandPacketBuffer, responsePacketBuffer, LINXDev.AOChans, LINXDev.numAOChans, L_OK);
       break;
	   
    case 0x000B: // Get PWM Channels
        dataBufferResponse(commandPacketBuffer, responsePacketBuffer, LINXDev.PWMChans, LINXDev.numPWMChans, L_OK);
       break;
	   
    case 0x000C: // Get QE Channels
        dataBufferResponse(commandPacketBuffer, responsePacketBuffer, LINXDev.QEChans, LINXDev.numQEChans, L_OK);
       break;
	   
    case 0x000D: // Get UART Channels
       dataBufferResponse(commandPacketBuffer, responsePacketBuffer, LINXDev.UARTChans, LINXDev.numUARTChans, L_OK);
       break;
	   
    case 0x000E: // Get I2C Channels
       dataBufferResponse(commandPacketBuffer, responsePacketBuffer, LINXDev.I2CChans, LINXDev.numI2CChans, L_OK);
       break;
	   
    case 0x000F: // Get SPI Channels
       dataBufferResponse(commandPacketBuffer, responsePacketBuffer, LINXDev.SPIChans, LINXDev.numSPIChans, L_OK);
       break;
	   
    case 0x0010: // Get CAN Channels
        dataBufferResponse(commandPacketBuffer, responsePacketBuffer, LINXDev.CANChans, LINXDev.numCANChans, L_OK);
       break;
		
	case 0x0011: // Disconnect
		//Nothing To Do Here.  This Function Will Return CMD To Network Stack Which Will Drop The Connection
		break;
		
	case 0x0024: // Get Device Name
		dataBufferResponse(commandPacketBuffer, responsePacketBuffer, LINXDev.deviceName, LINXDev.deviceNameLen, L_OK);
		break;
	
	/****************************************************************************************
	**  Digital I/O
	****************************************************************************************/	
	case 0x0041: // Get Device Name
		LINXDev.digitalWrite(commandPacketBuffer[6], &commandPacketBuffer[7], &commandPacketBuffer[7+commandPacketBuffer[6]]);
		statusResponse(commandPacketBuffer, responsePacketBuffer, L_OK);
		break;
		
	/****************************************************************************************
	**  Analog I/O
	****************************************************************************************/	
	case 0x0061: // Get AI Reference Voltage
		responsePacketBuffer[5] = (LINXDev.AIRef>>24) & 0xFF;		//AIREF MSB
		responsePacketBuffer[6] = (LINXDev.AIRef>>16) & 0xFF;		//...
		responsePacketBuffer[7] = (LINXDev.AIRef>>8) & 0xFF;			//...
		responsePacketBuffer[8] = LINXDev.AIRef & 0xFF;					//AIREF LSB
		packetize(commandPacketBuffer, responsePacketBuffer, 4, L_OK); 
		break;
		
	/****************************************************************************************
	** SPI
	****************************************************************************************/	
	case 0x0100: // SPI Open Masters
		LINXDev.SPIOpenMaster(commandPacketBuffer[6]);
		statusResponse(commandPacketBuffer, responsePacketBuffer, L_OK);
		break;
	case 0x0101: // SPI Set Bit Order
		LINXDev.SPISetBitOrder(commandPacketBuffer[6], commandPacketBuffer[7]);
		statusResponse(commandPacketBuffer, responsePacketBuffer, L_OK);
		break;
		
	case 0x0102: // SPI Set Clock Frequency				
	{
		unsigned long actualFreq = 0;
		SPIStatus spiStatus = LINXDev.SPISetSpeed( commandPacketBuffer[6], (unsigned long)((commandPacketBuffer[7] << 24) | (commandPacketBuffer[8] << 16) | (commandPacketBuffer[9] << 8) | commandPacketBuffer[10]), &actualFreq );
		//Build Response Packet
		responsePacketBuffer[5] = (actualFreq>>24) & 0xFF;		//Actual Freq MSB
		responsePacketBuffer[6] = (actualFreq>>16) & 0xFF;		//...
		responsePacketBuffer[7] = (actualFreq>>8) & 0xFF;			//...
		responsePacketBuffer[8] = actualFreq & 0xFF;					//Actual Freq LSB		
		packetize(commandPacketBuffer, responsePacketBuffer, 4, L_OK); 
		break;		
	}	
	case 0x0103: // SPI Set Mode
	{
		//Set SPI Mode
		SPIStatus spiStatus = LINXDev.SPISetMode(commandPacketBuffer[6], commandPacketBuffer[7]);
		
		//Check For Errors
		if(spiStatus != LSPI_OK)
		{
			Lstatus = L_UNKNOWN_ERROR;
		}
		else
		{
			Lstatus = L_OK;
		}
		
		//Build Response Packet
		packetize(commandPacketBuffer, responsePacketBuffer, 4, Lstatus); 
		break;	
	}
	case 0x0107: // SPI Write Read
	{
		
		SPIStatus spiStatus = LINXDev.SPIWriteRead(commandPacketBuffer[6], commandPacketBuffer[7], (commandPacketBuffer[1]-11)/commandPacketBuffer[7], commandPacketBuffer[8], commandPacketBuffer[9], &commandPacketBuffer[10], &responsePacketBuffer[5]);
		
		if(spiStatus != LSPI_OK)
		{
			packetize(commandPacketBuffer, responsePacketBuffer, commandPacketBuffer[7], L_UNKNOWN_ERROR); 
		}
		else
		{
			packetize(commandPacketBuffer, responsePacketBuffer, commandPacketBuffer[7], L_OK); 
		}
		break;
	}
	
	default: //Default Case
		statusResponse(commandPacketBuffer, responsePacketBuffer, L_FUNCTION_NOT_SUPPORTED);
		break;		
	}
	
	//Print Response Packet If Debugging Is Enabled
	DEBUGRESPACKET(responsePacketBuffer);	
	
	return Lstatus;
}


void packetize(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer, unsigned int dataSize, LINXStatus status)
{
	//Load Header
	responsePacketBuffer[0] = 0xFF;                                 //SoF
	responsePacketBuffer[1] = dataSize+6; 						//PACKET SIZE
	responsePacketBuffer[2] = commandPacketBuffer[2];	//PACKET NUM (MSB)
	responsePacketBuffer[3] = commandPacketBuffer[3];	//PACKET NUM (LSB)
	responsePacketBuffer[4] = status;								//Status
	
	//Compute And Load Checksum
	responsePacketBuffer[dataSize+5] = computeChecksum(responsePacketBuffer);	
}

#ifdef DEBUG_ENABLED
	void DEBUGCMDPACKET(unsigned char* packetBuffer)
	{
		fprintf(stdout, "Received : ");		
		for(int i =0; i<packetBuffer[1]; i++)
		{
			fprintf(stdout, "[%X] ", packetBuffer[i]);
		}	
		fprintf(stdout, "\n");
	}
#endif //DEBUG_ENABLED

#ifdef DEBUG_ENABLED
void debug_printResPacket(unsigned char* packetBuffer)
{
	fprintf(stdout, "Replying With : ");
	for(int i=0; i<packetBuffer[1]; i++)
	{
		fprintf(stdout, "[%X] ", packetBuffer[i]);
	}	
	fprintf(stdout, "\n");
}
#endif //DEBUG_ENABLED

void dataBufferResponse(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer, const unsigned char* dataBuffer, unsigned char dataSize, LINXStatus status)
{
	
	//Copy Data Into Response Buffer
	for(int i=0; i<dataSize; i++)
	{
		responsePacketBuffer[i+5] = dataBuffer[i];
	}
	
	packetize(commandPacketBuffer, responsePacketBuffer, dataSize, status);
}