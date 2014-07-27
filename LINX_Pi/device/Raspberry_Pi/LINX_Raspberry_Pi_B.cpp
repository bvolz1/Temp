#include "LINX_Raspberry_Pi_B.h"

/****************************************************************************************
**  Constructors
****************************************************************************************/
LINXRaspberryPi_B::LINXRaspberryPi_B()
{
	//Set Raspberry Pi Family And Model Number
	deviceFamily = DEVICE_FAMILY;
	deviceID = DEVICE_ID;
	deviceNameLen = DEVICENAMELEN;
	deviceName = c_deviceName;
	
	//LINX API Version
	linxAPIMajor = LINX_API_MAJOR;
	linxAPIMinor = LINX_API_MINOR;
	linxAPISubminor = LINX_API_SUBMINOR;
	
	//DIOChans;	
	numDIOChans = NUMDIOCHANS;
	DIOChans = c_DIOChans;
}

/****************************************************************************************
**  Functions
****************************************************************************************/

