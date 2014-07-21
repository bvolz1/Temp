#include <stdio.h>
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
