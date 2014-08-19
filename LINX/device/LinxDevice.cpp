/****************************************************************************************
**  Includes
****************************************************************************************/
#include <stdio.h>
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

//Reverse The Order Of Bits In A Byte.  This Is Useful For SPI Hardware That Does Not Support Bit Order
unsigned char LINXDevice::reverseBits(unsigned char b) 
{
	b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
	b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
	b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
	return b;
}