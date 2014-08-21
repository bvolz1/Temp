#ifndef LINX_RASPBERRY_PI_B_H
#define LINX_RASPBERRY_PI_B_H


/****************************************************************************************
**  Defines
****************************************************************************************/	
#define DEVICE_NAME_LEN 21
#define NUM_DIGITAL_CHANS 17

#define NUM_SPI_CHANS 1
#define NUM_SPI_SPEEDS 13

#define NUM_I2C_CHANS 2

#define NUM_UART_CHANS 1
#define NUM_UART_SPEEDS 19

/****************************************************************************************
**  Includes
****************************************************************************************/		
#include "LinxRaspberryPi.h"
	
class LinxRaspberryPiB : public LinxRaspberryPi
{
	public:	
		/****************************************************************************************
		**  Variables
		****************************************************************************************/		
		//System
		static const unsigned char m_DeviceName[DEVICE_NAME_LEN];
		
		//DIGITAL
		static const unsigned char m_DigitalChans[NUM_DIGITAL_CHANS];
		
		//SPI
		static const unsigned char m_SpiChans[NUM_SPI_CHANS];
		static int m_SpiHandles[NUM_SPI_CHANS];
		static const char m_SpiPaths[NUM_SPI_CHANS][SPI_PATH_LEN];
		static unsigned long m_SpiSupportedSpeeds[NUM_SPI_SPEEDS];
		static unsigned long m_SpiSetSpeeds[NUM_SPI_CHANS];
		static unsigned char m_SpiBitOrders[NUM_SPI_CHANS];
		
		//I2C
		static unsigned char m_I2cChans[NUM_I2C_CHANS];
		static int m_I2cHandles[NUM_I2C_CHANS];
		static const char m_I2cPaths[NUM_I2C_CHANS][I2C_PATH_LEN];
		
		//UART
		static unsigned char m_UartChans[NUM_UART_CHANS];
		static int m_UartHandles[NUM_UART_CHANS];
		static const char m_UartPaths[NUM_UART_CHANS][UART_PATH_LEN];
		static unsigned long m_UartSupportedSpeeds[NUM_UART_SPEEDS];
		static unsigned long m_UartSupportedSpeedsCodes[NUM_UART_SPEEDS];
		
		/****************************************************************************************
		**  Constructors /  Destructor
		****************************************************************************************/
		LinxRaspberryPiB();
		
		~LinxRaspberryPiB();
			
		/****************************************************************************************
		**  Functions
		****************************************************************************************/
		
	private:
		/****************************************************************************************
		**  Variables
		****************************************************************************************/		
				
		
		/****************************************************************************************
		**  Functions
		****************************************************************************************/
		
		
};


#endif //LINX_RASPBERRY_PI_B_H
