/****************************************************************************************
**  Defines
****************************************************************************************/

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

#include "device/LinxDevice.h"
#include "device/raspberrypi/LinxRaspberryPi.h"
#include "device/raspberrypi/LinxRaspberryPi-B.h"

#include "listener/LinxListener.h"
#include "listener/LinxTcpListener.h"
#include "listener/linux/LinxTcpListenerLinux.h"

/****************************************************************************************
** Variables
****************************************************************************************/
LinxRaspberryPiB LinxDev;	
LinxTcpListenerLinux LinxServer;

int main(int argc, char *argv[])
{

	//LinxDev.DebugPrint((char*)"\nStarting LVH LINX Daemon...");
	
	//Start LINX TCP Server	
	while(1)
	{	
	
		//TCP Server State Machine
		switch(LinxServer.State)
		{
			case START:
				//LinxDev.DebugPrint((char*)"Start State");
				LinxServer.Start(6999);
				break;
			
			case LISTENING:
				//LinxDev.DebugPrint((char*)"Listening State");
				LinxServer.Accept(LinxDev);
				break;	
			
			case AVAILABLE:
				break;
				
			case ACCEPT:
				break;
				
			case CONNECTED:
				//LinxDev.DebugPrint((char*)"Connected State");
				LinxServer.Connected(LinxDev);
				break;

			case CLOSE:
				//LinxDev.DebugPrint((char*)"Restarting LINX Server");
				LinxServer.Close();
				LinxServer.State = START;
				break;					
				
			case EXIT:
				//LinxDev.DebugPrint((char*)"Exit State\n");
				LinxServer.Exit();
				exit(-1);
				break;				
		}

	}
	
}
