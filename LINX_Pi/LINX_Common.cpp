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
