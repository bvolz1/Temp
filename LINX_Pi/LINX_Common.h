#ifndef LINX_COMMON_H
#define LINX_COMMON_H

/****************************************************************************************
** Variables
****************************************************************************************/
enum LINXStatus {OK, FUNCTION_NOT_SUPPORTED, REQUEST_RESEND};

/****************************************************************************************
** Functions
****************************************************************************************/

void debugPrint(char* message);
void debugPrintln(char* message);
unsigned long getSeconds();
//void processCommand(unsigned char* recBuffer, unsigned char* sendBuffer );
unsigned char computeChecksum(unsigned char* packetBuffer);
bool checksumPassed(unsigned char* packetBuffer);


#endif //LINX_COMMON_H