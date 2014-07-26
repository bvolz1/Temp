#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "LINX_Config.h"
#include "LINX_Common.h"

void debugPrint(char* message)
{
	if(DEBUG_ENABLED)
	{
		fprintf(stdout, message);
	}		
}

void debugPrintln(char* message)
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


void processCommand(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer, LINXDevice LINXDev)
{
	debugPrintln("LINXDev Processing Command ");
		
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
		
	default: //Default Case
		statusResponse(commandPacketBuffer, responsePacketBuffer, FUNCTION_NOT_SUPPORTED);
		break;		
	}
}



void packetize(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer, unsigned int dataSize, LINXStatus status)
{
	//Load Header
	responsePacketBuffer[0] = 0xFF;                                 //SoF
	responsePacketBuffer[1] = 0x08;                                //PACKET SIZE
	responsePacketBuffer[2] = commandPacketBuffer[2];	//PACKET NUM (MSB)
	responsePacketBuffer[3] = commandPacketBuffer[3];	//PACKET NUM (LSB)
	responsePacketBuffer[4] = status;								//Status
	
	//Compute And Load Checksum
	responsePacketBuffer[dataSize+5] = computeChecksum(responsePacketBuffer);	
}