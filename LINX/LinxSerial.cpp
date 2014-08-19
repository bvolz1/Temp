/****************************************************************************************
**  Includes
****************************************************************************************/		
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "LINX_Common.h"
#include "LinxSerialDaemon.h"	//To Do - Use Compiler Flags To Include Devices Specific Serial Daemon

/****************************************************************************************
**  Variables
****************************************************************************************/		

LinxSerialDaemon LinxSerialConnection;	//To Do - Use Compiler Flags To Instantiate Device Specific Serial Daemon

int main()
{
	DEBUG("Starting LINX Serial Daemon...\n");
	
	switch(LinxSerialConnection.State)
	{
		case START:
			LinxSerialConnection.Start(1, 2);
		break;
		
		case LISTENING:
			LinxSerialConnection.Listen();
		break;
		
		case Exit:
			LinxSerialConnection.Drop();
			return 0;
		break;
		
		default
			//Unknown State Exit
			LinxSerialConnection = EXIT;
		break;
	
	}
	
	return 0;

}