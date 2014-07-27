#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "LINX_Config.h"
#include "LINX_Common.h"

void debug_Print(char* message)
{
	if(DEBUG_ENABLED)
	{
		fprintf(stdout, message);
	}		
}

void debug_Println(char* message)
{
	if(DEBUG_ENABLED)
	{
		fprintf(stdout, message);
		fprintf(stdout, "\n");
	}		
}

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


int processCommand(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer, LINXDevice LINXDev)
{
	debug_printCmdPacket(commandPacketBuffer);
		
	//Store Some Local Values For Convenience
	unsigned char commandLength = commandPacketBuffer[1];
	unsigned int command = commandPacketBuffer[4] << 8 | commandPacketBuffer[5];
	
	switch(command)
  {
    /************************************************************************************
    * SYSTEM COMMANDS
    ************************************************************************************/
	case 0x0000: // Sync Packet        
		statusResponse(commandPacketBuffer, responsePacketBuffer, OK);
		break;
	 
	case 0x0003: // Get Device ID     
		responsePacketBuffer[5] = LINXDev.deviceFamily;
		responsePacketBuffer[6] = LINXDev.deviceID;    
		packetize(commandPacketBuffer, responsePacketBuffer, 2, OK); 
		break;	
		
	case 0x0004: //Get LINX API Version
		responsePacketBuffer[5] = LINXDev.linxAPIMajor;
		responsePacketBuffer[6] = LINXDev.linxAPIMinor;
		responsePacketBuffer[7] = LINXDev.linxAPISubminor;   
		packetize(commandPacketBuffer, responsePacketBuffer, 3, OK); 
		break;
		
	case 0x0008: // Get DIO Channels
		dataBufferResponse(commandPacketBuffer, responsePacketBuffer, LINXDev.DIOChans, LINXDev.numDIOChans, OK);
		break;
		
	case 0x0011: // Disconnect
		//Nothing To Do Here.  This Function Will Return CMD To Network Stack Which Will Drop The Connection
		break;
		
	case 0x0024: // Get Device Name
		dataBufferResponse(commandPacketBuffer, responsePacketBuffer, LINXDev.deviceName, LINXDev.deviceNameLen, OK);
		break;
		
	default: //Default Case
		statusResponse(commandPacketBuffer, responsePacketBuffer, FUNCTION_NOT_SUPPORTED);
		break;		
	}
	debug_printResPacket(responsePacketBuffer);
	return command;
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


void debug_printCmdPacket(unsigned char* packetBuffer)
{
	if(DEBUG_ENABLED)
	{	
		fprintf(stdout, "Received : ");		
		for(int i =0; i<packetBuffer[1]; i++)
		{
			fprintf(stdout, "[%X] ", packetBuffer[i]);
		}	
		fprintf(stdout, "\n");
	}	
}

void debug_printResPacket(unsigned char* packetBuffer)
{
	if(DEBUG_ENABLED)
	{	
		fprintf(stdout, "Replying With : ");
		for(int i=0; i<packetBuffer[1]; i++)
		{
			fprintf(stdout, "[%X] ", packetBuffer[i]);
		}	
		fprintf(stdout, "\n");
	}		
}


void dataBufferResponse(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer, const unsigned char* dataBuffer, unsigned char dataSize, LINXStatus status)
{
	fprintf(stdout, "Name Size = %d", dataSize);
	//Copy Data Into Response Buffer
	for(int i=0; i<dataSize; i++)
	{
		responsePacketBuffer[i+5] = dataBuffer[i];
	}
	
	packetize(commandPacketBuffer, responsePacketBuffer, dataSize, status);
}