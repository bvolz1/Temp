#include <stdio.h>

#include "../LINX_Common.h"
#include "LINX_Device.h"


/****************************************************************************************
**  Constructors
****************************************************************************************/
LINXDevice::LINXDevice()
{
	deviceFamily = 0xFE;
	deviceID = 0x00;
}

/****************************************************************************************
**  Functions
****************************************************************************************/
/*
int LINXDevice::digitalWrite(unsigned char numPins, unsigned char* pins, unsigned char* values)
{
	DEBUG("DigitalWrite At LINX Level");
	return -1;
}
*/