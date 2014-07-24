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