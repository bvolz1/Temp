#ifndef LINX_COMMON_H
#define LINX_COMMON_H

#include "device/LINX_Device.h"

/****************************************************************************************
** Variables
****************************************************************************************/
enum LINXStatus {OK, FUNCTION_NOT_SUPPORTED, REQUEST_RESEND};

/****************************************************************************************
** Functions
****************************************************************************************/
//LINX Helpers
void processCommand(unsigned char* recBuffer, unsigned char* sendBuffer, LINXDevice LINXDev);
void packetize(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer, unsigned int dataSize, LINXStatus status);
void statusResponse(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer, LINXStatus status);
unsigned char computeChecksum(unsigned char* packetBuffer);
bool checksumPassed(unsigned char* packetBuffer);

//Debugging
void debugPrint(char* message);
void debugPrintln(char* message);

//Misc
unsigned long getSeconds();

#endif //LINX_COMMON_H