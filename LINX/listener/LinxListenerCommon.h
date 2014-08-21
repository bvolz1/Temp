#ifndef LINX_LISTENER_COMMON_H
#define LINX_LISTENER_COMMON_H

/****************************************************************************************
** Includes
****************************************************************************************/
#include "../device/LinxDevice.h"


/****************************************************************************************
** Functions
****************************************************************************************/
int ProcessCommand(unsigned char* recBuffer, unsigned char* sendBuffer, LinxDevice& LinxDev);
void PacketizeAndSend(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer, unsigned int dataSize, int status);
void StatusResponse(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer, int status);
void DataBufferResponse(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer, const unsigned char* dataBuffer, unsigned char dataSize, int status);
unsigned char ComputeChecksum(unsigned char* packetBuffer);
bool ChecksumPassed(unsigned char* packetBuffer);


#endif //LINX_LISTENER_COMMON_H