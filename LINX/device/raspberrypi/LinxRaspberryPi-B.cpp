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
const unsigned char LinxRaspberryPiB::m_DeviceName[DEVICE_NAME_LEN] = "Raspberry Pi Model B";

//DIO
const unsigned char LinxRaspberryPiB::m_DigitalChans[NUM_DIGITAL_CHANS] = {2, 3, 4, 7, 8, 9, 10, 11, 14, 15, 17, 18, 22, 23, 24, 25, 27};

//SPI
const unsigned char LinxRaspberryPiB::m_SpiChans[NUM_SPI_CHANS] = {0};
int  LinxRaspberryPiB::m_SpiHandles[NUM_SPI_CHANS];
const char LinxRaspberryPiB::m_SpiPaths[NUM_SPI_CHANS][SPI_PATH_LEN] = { "/dev/spidev0.0\00" };
unsigned long LinxRaspberryPiB::m_SpiSupportedSpeeds[NUM_SPI_SPEEDS] = {7629, 15200, 30500, 61000, 122000, 244000, 488000, 976000, 1953000, 3900000, 7800000, 15600000, 31200000};
unsigned long LinxRaspberryPiB::m_SpiSetSpeeds[NUM_SPI_CHANS] = {500000};
unsigned char LinxRaspberryPiB::m_SpiBitOrders[NUM_SPI_CHANS] = {MSBFIRST};

//I2C
unsigned char LinxRaspberryPiB::m_I2cChans[NUM_I2C_CHANS] = {0, 1};
int LinxRaspberryPiB::m_I2cHandles[NUM_I2C_CHANS];
const char LinxRaspberryPiB::m_I2cPaths[NUM_I2C_CHANS][I2C_PATH_LEN] = { "/dev/i2c-0\00", "/dev/i2c-1\00" };

//UART
unsigned char LinxRaspberryPiB::m_UartChans[NUM_UART_CHANS] = {0};
int LinxRaspberryPiB::m_UartHandles[NUM_UART_CHANS];
const char LinxRaspberryPiB::m_UartPaths[NUM_UART_CHANS][UART_PATH_LEN] = { "/dev/ttyAMA0\00" };
unsigned long LinxRaspberryPiB::m_UartSupportedSpeeds[NUM_UART_SPEEDS] = {0, 50, 75, 110, 134, 150, 200, 300, 600, 1200, 1800, 2400, 4800, 9600, 19200, 38400, 57600, 115200, 230400};
unsigned long LinxRaspberryPiB::m_UartSupportedSpeedsCodes[NUM_UART_SPEEDS] = {B0, B50, B75, B110, B134, B150, B200, B300, B600, B1200, B1800, B2400, B4800, B9600, B19200, B38400, B57600, B115200, B230400};
	

/****************************************************************************************
**  Constructors /  Destructor
****************************************************************************************/
LinxRaspberryPiB::LinxRaspberryPiB()
{
	//Set Raspberry Pi Family And Model Number	
	DeviceID = 0x01;
	DeviceNameLen = DEVICE_NAME_LEN;	 
	DeviceName =  m_DeviceName;

	//LINX API Version
	LinxApiMajor = 1;
	LinxApiMinor = 1;
	LinxApiSubminor = 0;
	
	//DIGITAL
	NumDigitalChans = NUM_DIGITAL_CHANS;			
	DigitalChans = m_DigitalChans;
	
	//AI
	NumAiChans = 0;
	AiChans = 0;
	AiResolution = 0;
	AiRef = 0;
	
	//AO
	NumAoChans = 0;
	AoChans = 0;
	
	//PWM
	NumPwmChans = 0;
	PwmChans = 0;
	
	//QE
	NumQeChans = 0;
	QeChans = 0;
	
	//UART
	NumUartChans = NUM_UART_CHANS;
	UartChans = m_UartChans;
	UartPaths = m_UartPaths;
	
	NumUartSpeeds = NUM_UART_SPEEDS;
	UartSupportedSpeeds = m_UartSupportedSpeeds;
	UartSupportedSpeedsCodes = m_UartSupportedSpeedsCodes;
	UartHandles = m_UartHandles;
	
	
	//I2C
	NumI2cChans = NUM_I2C_CHANS;	
	I2cChans = m_I2cChans;
	I2cPaths = m_I2cPaths;
	I2cHandles = m_I2cHandles;
	
	//SPI
	NumSpiChans = NUM_SPI_CHANS;	
	SpiChans = m_SpiChans;		
	SpiPaths = m_SpiPaths;
	SpiHandles = m_SpiHandles;
	
	NumSpiSpeeds = NUM_SPI_SPEEDS;
	SpiSupportedSpeeds = m_SpiSupportedSpeeds;
	SpiSetSpeeds = m_SpiSetSpeeds;	
	SpiBitOrders = m_SpiBitOrders;
	
	//CAN
	NumCanChans = 0;
	CanChans = 0;
	
	
	//Export GPIO
	GpioExport(DigitalChans, NumDigitalChans);
}

//Destructor
LinxRaspberryPiB::~LinxRaspberryPiB()
{
	//Unexport GPIO
	GpioUnexport(DigitalChans, NumDigitalChans);
}

/****************************************************************************************
**  Functions
****************************************************************************************/

