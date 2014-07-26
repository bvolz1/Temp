#ifndef LINX_DEVICE_CONFIG_H
#define LINX_DEVICE_CONFIG_H

//Pull In The Device Specific Headers

//Default To Unknown Family And ID
#ifndef DEVICE_FAMILY
#define DEVICE_FAMILY 0xFE
#endif

#ifndef DEVICE_ID
#define DEVICE_ID 0x00
#endif


#if DEVICE_FAMILY == 0x04
	//Raspberry Pi
	#include "Raspberry_Pi/LINX_Raspberry_Pi_Config.h"
#endif


#endif //LINX_DEVICE_CONFIG_H