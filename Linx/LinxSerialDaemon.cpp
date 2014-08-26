/****************************************************************************************
**  Defines
****************************************************************************************/

/****************************************************************************************
**  Includes
****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "LinxCommon.h"
#include "device/LinxDevice.h"
#include "device/raspberrypi/LinxRaspberryPi-B.h"

#include "listener/LinxSerialListener.h"

/****************************************************************************************
** Variables
****************************************************************************************/
LinxSerialListener LinxConnection;
LinxRaspberryPiB LinxDev;	

int main(int argc, char *argv[])
{

	DEBUG("\nStarting LVH LINX Serial Daemon...");
	
	//Start LINX TCP Server	
	while(1)
	{	
	
		//TCP Server State Machine
		switch(LinxConnection.State)
		{
			case START:
				DEBUG("Start State");
				LinxConnection.Start(LinxDev, 0);
				break;
										
			case CONNECTED:
				//DEBUG("Connected State");
				LinxConnection.Connected(LinxDev);
				break;

			case CLOSE:
				DEBUG("Restarting LINX Server");
				LinxConnection.Close();
				LinxConnection.State = START;
				break;					
				
			case EXIT:
				DEBUG("Exit State\n");
				LinxConnection.Exit();
				exit(-1);
				break;				
		}

	}
	
}
