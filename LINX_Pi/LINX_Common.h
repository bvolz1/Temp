#ifndef LINX_COMMON_H
#define LINX_COMMON_H

/****************************************************************************************
** Functions
****************************************************************************************/

void debugPrint(char* message);
void debugPrintln(char* message);
unsigned long getSeconds();
void processCommand(unsigned char* recBuffer, unsigned char* sendBuffer );

#endif //LINX_COMMON_H