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



//Arduino
#if DEVICE_FAMILY == 2
	#define LINXWIRING 1
	#include "../device/wiring/arduino/LinxArduino.h"
	#if DEVICE_ID == 0
		#define LINXDEVICE LinxArduinoUno
		#include "../device/wiring/arduino/uno/LinxArduinoUno.h"
	#endif
#endif


//Digilent / ChipKIT
#if DEVICE_FAMILY == 1
	#define LINXWIRING 1
	#include "../device/wiring/chipkit/LinxChipkit.h"
	#if DEVICE_ID == 2
		#define LINXDEVICE LinxChipkitMax32
		#include "../device/wiring/chipkit/max32/LinxChipkitMax32.h"
	#endif
#endif


#if LINXRASPBERRYPI
	#include "../device/raspberrypi/LinxRaspberryPi.h"	
	#include "../device/raspberrypi/LinxRaspberryPi-B.h"	
#endif

//Device Specific
#if LINXWIRING
	#include "../device/wiring/LinxWiringDevice.h"
#endif


/****************************************************************************************
** Variables
****************************************************************************************/
LinxSerialListener LinxConnection;
LINXDEVICE LinxDev;	

#if LINXWIRING
	void setup()
	{
		//DEBUG!!!
		Serial1.begin(9600);
		Serial1.println("Starting Linx Serial Daemon...");
	}
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
