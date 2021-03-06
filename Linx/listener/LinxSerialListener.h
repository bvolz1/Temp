#ifndef LINX_SERIAL_LISTENER_H
#define LINX_SERIAL_LISTENER_H

/****************************************************************************************
**  Defines
****************************************************************************************/		
#define LINX_SERIAL_BUFFER_SIZE 64

/****************************************************************************************
**  Includes
****************************************************************************************/		
#include "LinxListener.h"
#include "../device/LinxDevice.h"

/****************************************************************************************
**  Type Defs
****************************************************************************************/		

/****************************************************************************************
**  Classes
****************************************************************************************/		
class LinxSerialListener : public LinxListener
{
	public:
		/****************************************************************************************
		**  Variables
		****************************************************************************************/		
		LinxListenerState State;
		//unsigned char LinxSerialListenerChan;
		
		/****************************************************************************************
		**  Constructors
		****************************************************************************************/
		LinxSerialListener();		//Default Constructor
		
		/****************************************************************************************
		**  Functions
		****************************************************************************************/		
		virtual int Start(LinxDevice &linxDev, unsigned char uartChan);			
		virtual int Connected(LinxDevice &linxDev);			
		virtual int Close();			
		virtual int Exit();			
		
	private:
		/****************************************************************************************
		**  Variables
		****************************************************************************************/		
				
		/****************************************************************************************
		**  Functions
		****************************************************************************************/
	
};

#endif //LINX_SERIAL_LISTENER_H