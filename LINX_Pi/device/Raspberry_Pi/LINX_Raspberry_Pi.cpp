#include <stdio.h>
#include <stdlib.h>

/****************************************************************************************
**  Includes
****************************************************************************************/		
#include "../../LINX_Config.h"
#include "../../LINX_Common.h"
#include "../LINX_Device.h"
#include "LINX_Raspberry_Pi.h"

/****************************************************************************************
**  Variables
****************************************************************************************/		

/****************************************************************************************
**  Constructors
****************************************************************************************/
LINXRaspberryPi::LINXRaspberryPi(RaspberryPiDevice deviceType)
{
	//Raspberry Pi Flavor Names
	unsigned char deviceName_A[20] = {'R', 'a', 's', 'p', 'b', 'e', 'r', 'r', 'y', ' ', 'P', 'i', ' ', 'M', 'o', 'd', 'e', 'l', ' ', 'A'};
	unsigned char deviceName_B[20] = {'R', 'a', 's', 'p', 'b', 'e', 'r', 'r', 'y', ' ', 'P', 'i', ' ', 'M', 'o', 'd', 'e', 'l', ' ', 'B'};
	unsigned char deviceName_BPlus[21] = {'R', 'a', 's', 'p', 'b', 'e', 'r', 'r', 'y', ' ', 'P', 'i', ' ', 'M', 'o', 'd', 'e', 'l', ' ', 'B', '+'};
	
	//Raspberry Pi Flavor DIO Channels
	const unsigned char DIOChans_A[17] = {2, 3, 4, 7, 8, 9, 10, 11, 14, 15, 17, 18, 22, 23, 24, 25, 27};
	const unsigned char DIOChans_B[17] = {2, 3, 4, 7, 8, 9, 10, 11, 14, 15, 17, 18, 22, 23, 24, 25, 27};
	//B+
	
	//Raspberry Pi Flavor QE Channels
	//None
	
	//Raspberry Pi Flavor UART Channels
	const unsigned char UARTChans_A[1] = {0};
	const unsigned char UARTChans_B[1] = {0};
	
	//Raspberry Pi Flavor I2C Channels
	const unsigned char I2CChans_A[1] = {0};
	const unsigned char I2CChans_B[1] = {0};
	
	//Raspberry Pi Flavor SPI Channels
	const unsigned char SPIChans_A[1] = {0};
	const unsigned char SPIChans_B[1] = {0};
	
	//Raspberry Pi Flavor CAN Channels
	const unsigned char CANChans_A[1] = {0};
	const unsigned char CANChans_B[1] = {0};
	//None
	
	//-----All-----
	deviceFamily = 0x04;
	
	//LINX API Version
	linxAPIMajor = 1;
	linxAPIMinor = 1;
	linxAPISubminor = 0;
	
	switch(deviceType)
	{
		case MODEL_A:
			//Set Raspberry Pi Family And Model Number	
			deviceID = 0x00;
			deviceNameLen = 20;			
			deviceName =  deviceName_A;
			
			//LINX API Version
			linxAPIMajor = 1;
			linxAPIMinor = 1;
			linxAPISubminor = 0;
			
			//DIOChans;	
			numDIOChans = 17;			
			DIOChans = DIOChans_A;			
			
			//AI
			numAIChans = 0;
			AIChans = 0;
			AIResolution = 0;
			AIRef = 0;
			
			//AO
			numAOChans = 0;
			AOChans = 0;
			
			//PWM
			numPWMChans = 0;
			PWMChans = 0;
			
			//QE
			numQEChans = 0;
			QEChans = NULL;
			
			//UART
			numUARTChans = 1;
			UARTChans = UARTChans_A;
			
			//I2C
			numI2CChans = 1;
			I2CChans = I2CChans_A;
			
			//SPI
			numSPIChans = 1;
			SPIChans =SPIChans_A;
			
			//CAN
			numCANChans = 0;
			CANChans = NULL;
			break;
			
		case MODEL_B:
			//Set Raspberry Pi Family And Model Number	
			deviceID = 0x01;
			deviceNameLen = 20;			
			deviceName =  deviceName_B;
			
			//LINX API Version
			linxAPIMajor = 1;
			linxAPIMinor = 1;
			linxAPISubminor = 0;
			
			//DIOChans;	
			numDIOChans = 17;			
			DIOChans = DIOChans_B;			
			
			//AI
			numAIChans = 0;
			AIChans = 0;
			AIResolution = 0;
			AIRef = 0;
			
			//AO
			numAOChans = 0;
			AOChans = 0;
			
			//PWM
			numPWMChans = 0;
			PWMChans = 0;
			
			//QE
			numQEChans = 0;
			QEChans = NULL;
			
			//UART
			numUARTChans = 1;
			UARTChans = UARTChans_B;
			
			//I2C
			numI2CChans = 1;
			I2CChans = I2CChans_B;
			
			//SPI
			numSPIChans = 1;
			SPIChans =SPIChans_B;
			
			//CAN
			numCANChans = 0;
			CANChans = NULL;
			break;
			
		case MODEL_B_PLUS:
			break;
	}	
}

/****************************************************************************************
**  Functions
****************************************************************************************/

