#ifndef LINX_COMMON_H
#define LINX_COMMON_H

/****************************************************************************************
** Includes
****************************************************************************************/
#include "device/LINX_Device.h"

/****************************************************************************************
** Defines
****************************************************************************************/
#ifdef DEBUG_ENABLED
	#define DEBUG(x) fprintf(stdout, x);fprintf(stdout, "\n")
	#define DEBUGCMDPACKET(x) debug_printCmdPacket(x)
	#define DEBUGRESPACKET(x) debug_printResPacket(x)
#else
	#define DEBUG(x) do {} while (0)									//Compile Out
	#define DEBUGCMDPACKET(x) do {} while (0)					//Compile Out
	#define DEBUGRESPACKET(x) do {} while (0)					//Compile Out
#endif	//DEBUG_ENABLED

/****************************************************************************************
** Typedefs
****************************************************************************************/
enum LINXStatus {L_OK, L_FUNCTION_NOT_SUPPORTED, L_REQUEST_RESEND, L_UNKNOWN_ERROR, L_DISCONNECT};

/****************************************************************************************
** Functions
****************************************************************************************/
//LINX Helpers
LINXStatus processCommand(unsigned char* recBuffer, unsigned char* sendBuffer, LINXDevice& LINXDev);
void packetize(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer, unsigned int dataSize, LINXStatus status);
void statusResponse(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer, LINXStatus status);
void dataBufferResponse(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer, const unsigned char* dataBuffer, unsigned char dataSize, LINXStatus status);
unsigned char computeChecksum(unsigned char* packetBuffer);
bool checksumPassed(unsigned char* packetBuffer);

//Debugging
void debug_Print(char* message);
void debug_Println(char* message);
void debug_printCmdPacket(unsigned char* packetBuffer);
void debug_printResPacket(unsigned char* packetBuffer);

//Misc
unsigned long getSeconds();

#endif //LINX_COMMON_H