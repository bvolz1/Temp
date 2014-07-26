#include <stdio.h>
#include <stdlib.h>

#include "../../LINX_Config.h"
#include "../../LINX_Common.h"
#include "../LINX_Device.h"
#include "LINX_Raspberry_Pi.h"


/****************************************************************************************
**  Constructors
****************************************************************************************/
LINXRaspberryPi::LINXRaspberryPi()
{
	//Set Raspberry Pi Family And Model Number
	deviceFamily = DEVICE_FAMILY;
	deviceID = DEVICE_ID;

	
	//DIOChans;
	//2, 3, 4, 7, 8, 9, 10, 11, 14, 15, 17, 18, 22, 23, 24, 25, 27
}

/****************************************************************************************
**  Functions
****************************************************************************************/

