/****************************************************************************************
**  Includes
****************************************************************************************/		
#include <stdio.h>
#include <string>
#include <termios.h>		//UART Support

#include "../../common/LinxCommon.h"
#include "../LinxDevice.h"
#include "LinxRaspberryPi-B.h"

/****************************************************************************************
**  Member Variables
****************************************************************************************/
//System
const unsigned char LINXRaspberryPi_B::m_deviceName[DEVICE_NAME_LEN] = {'R', 'a', 's', 'p', 'b', 'e', 'r', 'r', 'y', ' ', 'P', 'i', ' ', 'M', 'o', 'd', 'e', 'l', ' ', 'B'};

//DIO
const unsigned char LINXRaspberryPi_B::m_DIOChans[NUM_DIO_CHANS] = {2, 3, 4, 7, 8, 9, 10, 11, 14, 15, 17, 18, 22, 23, 24, 25, 27};

//SPI
const unsigned char LINXRaspberryPi_B::m_SPIChans[NUM_SPI_CHANS] = {0};
int  LINXRaspberryPi_B::m_SPIHandles[NUM_SPI_CHANS];
const char LINXRaspberryPi_B::m_SPIPaths[NUM_SPI_CHANS][SPI_PATH_LEN] = { "/dev/spidev0.0\00" };
unsigned long LINXRaspberryPi_B::m_SPISupportedSpeeds[NUM_SPI_SPEEDS] = {7629, 15200, 30500, 61000, 122000, 244000, 488000, 976000, 1953000, 3900000, 7800000, 15600000, 31200000};
unsigned long LINXRaspberryPi_B::m_SPISetSpeeds[NUM_SPI_CHANS] = {500000};
unsigned char LINXRaspberryPi_B::m_SPIBitOrders[NUM_SPI_CHANS] = {MSBFIRST};

//I2C
unsigned char LINXRaspberryPi_B::m_I2CChans[NUM_I2C_CHANS] = {0, 1};
int LINXRaspberryPi_B::m_I2CHandles[NUM_I2C_CHANS];
const char LINXRaspberryPi_B::m_I2CPaths[NUM_I2C_CHANS][I2C_PATH_LEN] = { "/dev/i2c-0\00", "/dev/i2c-1\00" };

//UART
unsigned char LINXRaspberryPi_B::m_UartChans[NUM_UART_CHANS] = {0};
int LINXRaspberryPi_B::m_UartHandles[NUM_UART_CHANS];
const char LINXRaspberryPi_B::m_UartPaths[NUM_UART_CHANS][UART_PATH_LEN] = { "/dev/ttyAMA0\00" };
unsigned long LINXRaspberryPi_B::m_UartSupportedSpeeds[NUM_UART_SPEEDS] = {0, 50, 75, 110, 134, 150, 200, 300, 600, 1200, 1800, 2400, 4800, 9600, 19200, 38400, 57600, 115200, 230400};
unsigned long LINXRaspberryPi_B::m_UartSupportedSpeedsCodes[NUM_UART_SPEEDS] = {B0, B50, B75, B110, B134, B150, B200, B300, B600, B1200, B1800, B2400, B4800, B9600, B19200, B38400, B57600, B115200, B230400};
	

/****************************************************************************************
**  Constructors /  Destructor
****************************************************************************************/
LINXRaspberryPi_B::LINXRaspberryPi_B()
{
	//Set Raspberry Pi Family And Model Number	
	deviceID = 0x01;
	deviceNameLen = DEVICE_NAME_LEN;	 
	deviceName =  m_deviceName;

	//LINX API Version
	linxAPIMajor = 1;
	linxAPIMinor = 1;
	linxAPISubminor = 0;
	
	//DIOChans;	
	numDIOChans = NUM_DIO_CHANS;			
	DIOChans = m_DIOChans;
	
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
	NumUartChans = NUM_UART_CHANS;
	UartChans = m_UartChans;
	UartPaths = m_UartPaths;
	
	NumUartSpeeds = NUM_UART_SPEEDS;
	UartSupportedSpeeds = m_UartSupportedSpeeds;
	UartSupportedSpeedsCodes = m_UartSupportedSpeedsCodes;
	UartHandles = m_UartHandles;
	
	
	//I2C
	numI2CChans = NUM_I2C_CHANS;	
	I2CChans = m_I2CChans;
	I2CPaths = m_I2CPaths;
	I2CHandles = m_I2CHandles;
	
	//SPI
	numSPIChans = NUM_SPI_CHANS;	
	SPIChans = m_SPIChans;		
	SPIPaths = m_SPIPaths;
	SPIHandles = m_SPIHandles;
	
	numSPISpeeds = NUM_SPI_SPEEDS;
	SPISupportedSpeeds = m_SPISupportedSpeeds;
	SPISetSpeeds = m_SPISetSpeeds;	
	SPIBitOrders = m_SPIBitOrders;
	
	//CAN
	numCANChans = 0;
	CANChans = 0;
	
	
	//Export GPIO
	GPIOExport(DIOChans, numDIOChans);
}

//Destructor
LINXRaspberryPi_B::~LINXRaspberryPi_B()
{
	//Unexport GPIO
	GPIOUnexport(DIOChans, numDIOChans);
}

/****************************************************************************************
**  Functions
****************************************************************************************/

