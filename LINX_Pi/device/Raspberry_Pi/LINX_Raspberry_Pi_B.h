#ifndef LINX_RASPBERRY_PI_B_H
#define LINX_RASPBERRY_PI_B_H

/****************************************************************************************
**  Includes
****************************************************************************************/		
#include "LINX_Raspberry_Pi.h"

/****************************************************************************************
**  Device Configuration
****************************************************************************************/		
//Device ID
#define DEVICE_ID 0x01
#define DEVICENAMELEN 20
const unsigned char c_deviceName[DEVICENAMELEN] = {'R', 'a', 's', 'p', 'b', 'e', 'r', 'r', 'y', ' ', 'P', 'i', ' ', 'M', 'o', 'd', 'e', 'l', ' ', 'B'};
#define LINX_API_MAJOR 1
#define LINX_API_MINOR 1
#define LINX_API_SUBMINOR 0

//Peripherals
#define NUMDIOCHANS 17
const unsigned char c_DIOChans[NUMDIOCHANS] = {2, 3, 4, 7, 8, 9, 10, 11, 14, 15, 17, 18, 22, 23, 24, 25, 27};
#define NUMAICHANS 0
const unsigned char c_AIChans[NUMDIOCHANS] = {};
#define AI_RESOLUTION 0
#define AI_REFERENCE 0
#define NUMAOCHANS 0
const unsigned char c_AOChans[] = {};
#define NUMPWMCHANS 0
const unsigned char c_PWMChans[] = {};
#define NUMQECHANS 0
const unsigned char c_QEChans[] = {};
#define NUMUARTCHANS 1
const unsigned char c_UARTChans[] = {0};
#define NUMI2CCHANS 1
const unsigned char c_I2CChans[] = {0};
#define NUMSPICHANS 1
const unsigned char c_SPIChans[] = {0};
#define NUMCANCHANS 0
const unsigned char c_CANChans[] = {};
		
class LINXRaspberryPi_B : public LINXRaspberryPi
{
	public:	
		/****************************************************************************************
		**  Variables
		****************************************************************************************/		
				
		//End Model B		
		/****************************************************************************************
		**  Constructors
		****************************************************************************************/
		LINXRaspberryPi_B();
			
		/****************************************************************************************
		**  Functions
		****************************************************************************************/
		
	private:
		/****************************************************************************************
		**  Variables
		****************************************************************************************/		
				
		
		/****************************************************************************************
		**  Functions
		****************************************************************************************/
		
		
};


#endif //LINX_RASPBERRY_PI_B_H
