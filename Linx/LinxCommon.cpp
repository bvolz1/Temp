#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "LinxCommon.h"
#include "device/LinxDevice.h"

unsigned long GetNanoSeconds()
{
	timespec mTime;
	clock_gettime(CLOCK_MONOTONIC, &mTime);	
	return mTime.tv_nsec;
}

unsigned long GetMicroSeconds()
{
	return GetNanoSeconds() / 1000;
}

unsigned long GetMilliSeconds()
{
	return GetNanoSeconds() / 1000000;
}

unsigned long GetSeconds()
{
	timespec mTime;
	clock_gettime(CLOCK_MONOTONIC, &mTime);	
	return mTime.tv_sec;
}

//DEBUG
#ifdef DEBUG_ENABLED
	void DebugPrintCmdPacket(unsigned char* packetBuffer)
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
void DebugPrintResPacket(unsigned char* packetBuffer)
{
	fprintf(stdout, "Replying With : ");
	for(int i=0; i<packetBuffer[1]; i++)
	{
		fprintf(stdout, "[%X] ", packetBuffer[i]);
	}	
	fprintf(stdout, "\n");
}
#endif //DEBUG_ENABLED
