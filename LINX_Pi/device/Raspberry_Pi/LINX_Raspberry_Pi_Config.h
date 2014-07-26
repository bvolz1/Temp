#ifndef LINX_RASPBERRY_PI_CONFIG_H
#define LINX_RASPBERRY_PI_CONFIG_H

#include "../LINX_Device_Config.h"

/****************************************************************************************
**  Models
**	0x00 - MODEL_A
**	0x01 - MODEL_B
**	0x02 - MODEL_B_PLUS
****************************************************************************************/


#if DEVICE_ID == 0x00		
//Model A

#elif DEVICE_ID == 0x01	
//Model B
#define NUMDIOCHANS 17

#elif DEVICE_ID == 0x02	
//Model B+

#endif

#endif //LINX_RASPBERRY_PI_CONFIG_H