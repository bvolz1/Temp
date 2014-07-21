


/****************************************************************************************
**  Includes
****************************************************************************************/
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#include "LINX_Config.h"
#include "LINX_Common.h"
#include "LINX_Networking.h"

/****************************************************************************************
** Variables
****************************************************************************************/
TCPServer LINXServer;

int main(int argc, char *argv[])
{

	debugPrintln("Starting LVH LINX");
	LINXServer.begin();

}