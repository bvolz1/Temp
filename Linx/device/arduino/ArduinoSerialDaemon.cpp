
#include "ArduinoSerialDaemon.h"

/****************************************************************************************
**  Constructors
****************************************************************************************/
ArduinoSerialDaemon::ArduinoSerialDaemon()
{
	State = START;	
}

/****************************************************************************************
**  Functions
****************************************************************************************/

int ArduinoSerialDaemon::Start(unsigned char channel, unsigned long buad)
{
	return -1;
}

int ArduinoSerialDaemon::Listen()
{
	return -1;
}

 int ArduinoSerialDaemon::Drop()
 {
	return -1;
 }
