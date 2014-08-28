#ifndef LINX_COMMON_H
#define LINX_COMMON_H

/****************************************************************************************
** Includes
****************************************************************************************/
#include "device/LinxDevice.h"

/****************************************************************************************
** Defines
****************************************************************************************/
#ifdef DEBUG_ENABLED
	#define DEBUG(x) fprintf(stdout, x);fprintf(stdout, "\n")
	#define DEBUGCMDPACKET(x) DebugPrintCmdPacket(x)
	#define DEBUGRESPACKET(x) DebugPrintResPacket(x)
#else
	#define DEBUG(x) do {} while (0)									//Compile Out
	#define DEBUGCMDPACKET(x) do {} while (0)					//Compile Out
	#define DEBUGRESPACKET(x) do {} while (0)					//Compile Out
#endif	//DEBUG_ENABLED

/****************************************************************************************
** Typedefs
****************************************************************************************/


/****************************************************************************************
** Functions
****************************************************************************************/
//Debugging
void DebugPrint(char* message);
void DebugPrintCmdPacket(unsigned char* packetBuffer);
void DebugPrintResPacket(unsigned char* packetBuffer);

//Misc
unsigned long GetNanoSeconds();
unsigned long GetMicroSeconds();
unsigned long GetMilliSeconds();
unsigned long GetSeconds();

#endif //LINX_COMMON_H