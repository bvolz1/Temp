/****************************************************************************************
**  Defines
****************************************************************************************/

/****************************************************************************************
**  Includes
****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Listener
#include "../listener/LinxListener.h"
#include "../listener/LinxSerialListener.h"

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
	#include "../device/raspberrypi/LinxRaspberryPi.h"	
	#include "../device/raspberrypi/LinxRaspberryPi-B.h"	
#endif



/****************************************************************************************
** Variables
****************************************************************************************/
LinxSerialListener LinxConnection;
LINXDEVICE LinxDev;	

#if LINXWIRING
	void setup(){};
	void loop()
#else
	int main(int argc, char *argv[])
#endif
{
	//Start LINX TCP Server	
	while(1)
	{	
	
		//TCP Server State Machine
		switch(LinxConnection.State)
		{
			case START:
				
				LinxConnection.Start(LinxDev, 0);
				break;
										
			case CONNECTED:
				//DEBUG("Connected State");
				LinxConnection.Connected(LinxDev);
				break;

			case CLOSE:
				
				LinxConnection.Close();
				LinxConnection.State = START;
				break;					
				
			case EXIT:

				LinxConnection.Exit();
				exit(-1);
				break;				
		}

	}
	
}
