#ifndef ARDUINO_SERIAL_DAEMON_H
#define ARDUINO_SERIAL_DAEMON

/****************************************************************************************
**  Includes
****************************************************************************************/		
#include "../../LinxSerialDaemon.h"

/****************************************************************************************
**  Variables
****************************************************************************************/		

class ArduinoSerialDaemon : public LinxSerialDaemon
{
	public:	
		/****************************************************************************************
		**  Variables
		****************************************************************************************/		
		
		
		/****************************************************************************************
		**  Constructors
		****************************************************************************************/
		ArduinoSerialDaemon();		//Default Constructor
	
		/****************************************************************************************
		**  Functions
		****************************************************************************************/
		
		//Open The Specified Serial Channel
		int Start(unsigned char channel, unsigned long buad);
		
		//Check Serial Input Buffer For Full Command Packet, If One Exists Process It
		int Listen();
		
		//Drop The Serial Connection And Return Values To Defaults.  This Could Be Called Before Exiting Or Before Restarting
		int Drop();
		
	private:		
};
#endif //ARDUINO_SERIAL_DAEMON