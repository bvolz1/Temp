/****************************************************************************************
**  Defines
****************************************************************************************/

/****************************************************************************************
**  Includes
****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../listener/LinxListener.h"
#include "../../listener/LinxSerialListener.h"

#include "../../device/LinxDevice.h"
#include "../../device/wiring/LinxWiringDevice.h"
#include "../../device/wiring/arduino/LinxArduino.h"
#include "../../device/wiring/arduino/uno/LinxArduinoUno.h"



/****************************************************************************************
** Variables
****************************************************************************************/
LinxSerialListener LinxConnection;
LinxArduinoUno LinxDev;	

int main(int argc, char *argv[])
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
