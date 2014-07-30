/****************************************************************************************
**  Includes
****************************************************************************************/		
#include "../../LINX_Common.h"
#include "../LINX_Device.h"
#include "LINX_Raspberry_Pi_B.h"

#define DEVICENAMELEN 20

/****************************************************************************************
**  Constructors
****************************************************************************************/
LINXRaspberryPi_B::LINXRaspberryPi_B()
{
	//Set Raspberry Pi Family And Model Number	
	deviceID = 0x01;
	deviceNameLen = 20;
	const unsigned char m_deviceName[20] = {'R', 'a', 's', 'p', 'b', 'e', 'r', 'r', 'y', ' ', 'P', 'i', ' ', 'M', 'o', 'd', 'e', 'l', ' ', 'B'};
	deviceName =  m_deviceName;
	
	//LINX API Version
	linxAPIMajor = 1;
	linxAPIMinor = 1;
	linxAPISubminor = 0;
	
	//DIOChans;	
	numDIOChans = 17;	
	const unsigned char DIOChans_B[17] = {2, 3, 4, 7, 8, 9, 10, 11, 14, 15, 17, 18, 22, 23, 24, 25, 27};	
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
	QEChans = 0;
	
	//UART
	numUARTChans = 1;
	const unsigned char m_UARTChans[1] = {0};
	UARTChans = m_UARTChans;
	
	//I2C
	numI2CChans = 1;
	const unsigned char m_I2CChans[1] = {0};
	I2CChans = m_I2CChans;
	
	//SPI
	numSPIChans = 1;
	const unsigned char m_SPIChans[1] = {0};
	SPIChans = m_SPIChans;
	
	//CAN
	numCANChans = 0;
	CANChans = 0;
}

/****************************************************************************************
**  Functions
****************************************************************************************/

