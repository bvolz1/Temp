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

#include "LinxCommon.h"
#include "device/LinxDevice.h"
#include "device/raspberrypi/LinxRaspberryPi-B.h"

#include "listener/LinxTcpListener.h"
#include "listener/linux/LinxTcpListenerLinux.h"

/****************************************************************************************
** Variables
****************************************************************************************/
LinxTcpListenerLinux LinxServer;
LinxRaspberryPiB LinxDev;	

int main(int argc, char *argv[])
{

	DEBUG("\nStarting LVH LINX Daemon...");
	
	//Start LINX TCP Server	
	while(1)
	{	
	
		//TCP Server State Machine
		switch(LinxServer.State)
		{
			case START:
				DEBUG("Start State");
				LinxServer.Start(6999);
				break;
			
			case LISTENING:
				DEBUG("Listening State");
				LinxServer.Accept();
				break;	
			
			case AVAILABLE:
				break;
				
			case ACCEPT:
				break;
				
			case CONNECTED:
				DEBUG("Connected State");
				LinxServer.Connected(LinxDev);
				break;

			case CLOSE:
				DEBUG("Restarting LINX Server");
				LinxServer.Close();
				LinxServer.State = START;
				break;					
				
			case EXIT:
				DEBUG("Exit State\n");
				LinxServer.Exit();
				exit(-1);
				break;				
		}

	}
	
}
