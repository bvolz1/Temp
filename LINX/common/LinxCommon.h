#ifndef LINX_COMMON_H
#define LINX_COMMON_H

/****************************************************************************************
** Includes
****************************************************************************************/
#include "../device/LinxDevice.h"

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
enum LinxStatus {L_OK, L_FUNCTION_NOT_SUPPORTED, L_REQUEST_RESEND, L_UNKNOWN_ERROR, L_DISCONNECT};

/****************************************************************************************
** Functions
****************************************************************************************/
//LINX Helpers
int ProcessCommand(unsigned char* recBuffer, unsigned char* sendBuffer, LinxDevice& LinxDev);
void PacketizeAndSend(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer, unsigned int dataSize, int status);
void StatusResponse(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer, int status);
void DataBufferResponse(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer, const unsigned char* dataBuffer, unsigned char dataSize, int status);
unsigned char ComputeChecksum(unsigned char* packetBuffer);
bool ChecksumPassed(unsigned char* packetBuffer);

//Debugging
void DebugPrint(char* message);
void DebugPrintCmdPacket(unsigned char* packetBuffer);
void DebugPrintResPacket(unsigned char* packetBuffer);

//Misc
unsigned long GetSeconds();

#endif //LINX_COMMON_H