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
	
	//AI
	numAIChans = NUMAICHANS;
	AIChans = c_AIChans;
	AIResolution = AI_RESOLUTION;
	AIRef = AI_REFERENCE;
	
	//AO
	numAOChans = NUMAOCHANS;
	AOChans = c_AOChans;
	
	//PWM
	numPWMChans = NUMPWMCHANS;
	PWMChans = c_PWMChans;
	
	//QE
	numQEChans = NUMQECHANS;
	QEChans = c_QEChans;
	
	//UART
	numUARTChans = NUMUARTCHANS;
	UARTChans = c_UARTChans;
	
	//I2C
	numI2CChans = NUMI2CCHANS;
	I2CChans = c_I2CChans;
	
	//SPI
	numSPIChans = NUMSPICHANS;
	SPIChans = c_SPIChans;
	
	//CAN
	numCANChans = NUMCANCHANS;
	CANChans = c_CANChans;
}

/****************************************************************************************
**  Functions
****************************************************************************************/

