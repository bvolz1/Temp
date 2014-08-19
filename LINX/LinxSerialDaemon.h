#ifndef LINX_SERIAL_DAEMON_H
#define LINX_SERIAL_DAEMON_H

/****************************************************************************************
**  Includes
****************************************************************************************/		
#include "device/LINX_Device.h"

//Variables
enum LinxSerialDaemonState {START, LISTENING, RESTART, EXIT};

class LinxSerialDaemon
{
	public:	
		/****************************************************************************************
		**  Variables
		****************************************************************************************/		
		LinxSerialDaemonState State;
		
		/****************************************************************************************
		**  Constructors
		****************************************************************************************/
		LinxSerialDaemon();		//Default Constructor
	
		/****************************************************************************************
		**  Functions
		****************************************************************************************/
		
		//Open The Specified Serial Channel
		virtual int Start(unsigned char channel, unsigned long buad);
		
		//Check Serial Input Buffer For Full Command Packet, If One Exists Process It
		virtual int Listen();
		
		//Drop The Serial Connection And Return Values To Defaults.  This Could Be Called Before Exiting Or Before Restarting
		virtual int Drop();
		
	private:
		/****************************************************************************************
		**  Variables
		****************************************************************************************/		
			
		/****************************************************************************************
		**  Functions
		****************************************************************************************/		
};

#endif //LINX_SERIAL_DAEMON