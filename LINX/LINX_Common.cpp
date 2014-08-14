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


void statusResponse(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer, int status)
{
	packetize(commandPacketBuffer, responsePacketBuffer, 0, status); 
}


int processCommand(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer, LINXDevice &LINXDev)
{
	DEBUGCMDPACKET(commandPacketBuffer);
		
	//Store Some Local Values For Convenience
	unsigned char commandLength = commandPacketBuffer[1];
	unsigned int command = commandPacketBuffer[4] << 8 | commandPacketBuffer[5];
	
	int status = L_OK;
	
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
		status = L_DISCONNECT;
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
	** I2C
	****************************************************************************************/	
	case 0x00E0: // I2C Open Master
		status = LINXDev.I2COpenMaster(commandPacketBuffer[6]);
		statusResponse(commandPacketBuffer, responsePacketBuffer, status);
		break;
	case 0x00E1: // I2C Set Speed
	{
		unsigned long targetSpeed = (unsigned long)((commandPacketBuffer[7] << 24) | (commandPacketBuffer[8] << 16) | (commandPacketBuffer[9] << 8) | commandPacketBuffer[10]);
		unsigned long actualSpeed = 0;
		status = LINXDev.I2CSetSpeed(commandPacketBuffer[6], targetSpeed, &actualSpeed);
		
		//Build Response Packet
		responsePacketBuffer[5] = (actualSpeed>>24) & 0xFF;		//Actual Speed MSB
		responsePacketBuffer[6] = (actualSpeed>>16) & 0xFF;		//...
		responsePacketBuffer[7] = (actualSpeed>>8) & 0xFF;			//...
		responsePacketBuffer[8] = actualSpeed & 0xFF;					//Actual Speed LSB		
		packetize(commandPacketBuffer, responsePacketBuffer, 4, status); 
		break;
	}
	case 0x00E2: // I2C Write
		status = LINXDev.I2CWrite(commandPacketBuffer[6], commandPacketBuffer[7], commandPacketBuffer[8], (commandPacketBuffer[1]-10), &commandPacketBuffer[9]);
		statusResponse(commandPacketBuffer, responsePacketBuffer, status);
		break;
	case 0x00E3: // I2C Read
		status = L_FUNCTION_NOT_SUPPORTED;
		statusResponse(commandPacketBuffer, responsePacketBuffer, status);
		break;
	case 0x00E4: // I2C Close
		status = LINXDev.I2CClose((commandPacketBuffer[6]));
		statusResponse(commandPacketBuffer, responsePacketBuffer, status);
		break;
		
	/****************************************************************************************
	** SPI
	****************************************************************************************/	
	case 0x0100: // SPI Open Master
		LINXDev.SPIOpenMaster(commandPacketBuffer[6]);
		statusResponse(commandPacketBuffer, responsePacketBuffer, L_OK);
		break;
	case 0x0101: // SPI Set Bit Order
		LINXDev.SPISetBitOrder(commandPacketBuffer[6], commandPacketBuffer[7]);
		statusResponse(commandPacketBuffer, responsePacketBuffer, L_OK);
		break;
		
	case 0x0102: // SPI Set Clock Frequency				
	{
		unsigned long targetSpeed = (unsigned long)((commandPacketBuffer[7] << 24) | (commandPacketBuffer[8] << 16) | (commandPacketBuffer[9] << 8) | commandPacketBuffer[10]);
		unsigned long actualSpeed = 0;
		status = LINXDev.SPISetSpeed( commandPacketBuffer[6], targetSpeed, &actualSpeed );
		//Build Response Packet
		responsePacketBuffer[5] = (actualSpeed>>24) & 0xFF;		//Actual Speed MSB
		responsePacketBuffer[6] = (actualSpeed>>16) & 0xFF;		//...
		responsePacketBuffer[7] = (actualSpeed>>8) & 0xFF;			//...
		responsePacketBuffer[8] = actualSpeed & 0xFF;					//Actual Speed LSB		
		packetize(commandPacketBuffer, responsePacketBuffer, 4, L_OK); 
		break;		
	}	
	case 0x0103: // SPI Set Mode
	{
		//Set SPI Mode
		status = LINXDev.SPISetMode(commandPacketBuffer[6], commandPacketBuffer[7]);
		
		//Build Response Packet
		packetize(commandPacketBuffer, responsePacketBuffer, 4, status); 
		break;	
	}
	case 0x0107: // SPI Write Read
	{
		status = LINXDev.SPIWriteRead(commandPacketBuffer[6], commandPacketBuffer[7], (commandPacketBuffer[1]-11)/commandPacketBuffer[7], commandPacketBuffer[8], commandPacketBuffer[9], &commandPacketBuffer[10], &responsePacketBuffer[5]);
		packetize(commandPacketBuffer, responsePacketBuffer, commandPacketBuffer[7]*commandPacketBuffer[8], status); 
		break;
	}
	
	default: //Default Case
		statusResponse(commandPacketBuffer, responsePacketBuffer, (int)L_FUNCTION_NOT_SUPPORTED);
		break;		
	}
	
	//Print Response Packet If Debugging Is Enabled
	DEBUGRESPACKET(responsePacketBuffer);	
	
	return status;
}


void packetize(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer, unsigned int dataSize,  int status)
{
	//Load Header
	responsePacketBuffer[0] = 0xFF;                                 //SoF
	responsePacketBuffer[1] = dataSize+6; 						//PACKET SIZE
	responsePacketBuffer[2] = commandPacketBuffer[2];	//PACKET NUM (MSB)
	responsePacketBuffer[3] = commandPacketBuffer[3];	//PACKET NUM (LSB)
	//Make Sure Status Is Valid
	if(status >= 0 && status <= 255)
	{
		responsePacketBuffer[4] = (unsigned char)status;	//Status
	}
	else
	{
		responsePacketBuffer[4] = (unsigned char)L_UNKNOWN_ERROR;	//Status
	}
	
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

void dataBufferResponse(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer, const unsigned char* dataBuffer, unsigned char dataSize, int status)
{
	
	//Copy Data Into Response Buffer
	for(int i=0; i<dataSize; i++)
	{
		responsePacketBuffer[i+5] = dataBuffer[i];
	}
	
	packetize(commandPacketBuffer, responsePacketBuffer, dataSize, status);
}