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

//Listener
#include "../listener/LinxListener.h"
#include "../listener/LinxTcpListener.h"

//Device Generic
#include "../device/LinxDevice.h"

//Device Specific
#if LINXWIRING
	#include "../device/wiring/LinxWiringDevice.h"
#endif

#if LINXARDUINO	
	#include "../device/wiring/arduino/LinxArduino.h"
	#include "../device/wiring/arduino/uno/LinxArduinoUno.h"
#endif

#if LINXRASPBERRYPI
	#include "../listener/linux/LinxTcpListenerLinux.h"
	#include "../device/raspberrypi/LinxRaspberryPi.h"	
	#include "../device/raspberrypi/LinxRaspberryPi-B.h"	
#endif


/****************************************************************************************
** Variables
****************************************************************************************/
LinxTcpListenerLinux LinxConnection;
LINXDEVICE LinxDev;	

#if LINXWIRING
	void setup(){};
	void loop()
#else
	int main(int argc, char *argv[])
#endif
{

	//LinxDev.DebugPrint((char*)"\nStarting LVH LINX Daemon...");
	
	//Start LINX TCP Server	
	while(1)
	{	
	
		//TCP Server State Machine
		switch(LinxConnection.State)
		{
			case START:
				//LinxDev.DebugPrint((char*)"Start State");
				LinxConnection.Start(6999);
				break;
			
			case LISTENING:
				//LinxDev.DebugPrint((char*)"Listening State");
				LinxConnection.Accept(LinxDev);
				break;	
			
			case AVAILABLE:
				break;
				
			case ACCEPT:
				break;
				
			case CONNECTED:
				//LinxDev.DebugPrint((char*)"Connected State");
				LinxConnection.Connected(LinxDev);
				break;

			case CLOSE:
				//LinxDev.DebugPrint((char*)"Restarting LINX Server");
				LinxConnection.Close();
				LinxConnection.State = START;
				break;					
				
			case EXIT:
				//LinxDev.DebugPrint((char*)"Exit State\n");
				LinxConnection.Exit();
				exit(-1);
				break;				
		}

	}
	
}
