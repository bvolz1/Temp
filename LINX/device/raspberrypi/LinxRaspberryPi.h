#ifndef LINX_RASPBERRY_PI_H
#define LINX_RASPBERRY_PI_H

/****************************************************************************************
**  Includes
****************************************************************************************/		
#include <string>
#include "../LinxDevice.h"


#define SPI_PATH_LEN 64
#define I2C_PATH_LEN 64
#define UART_PATH_LEN 64

/****************************************************************************************
**  Variables
****************************************************************************************/		

class LINXRaspberryPi : public LINXDevice
{
	public:	
		/****************************************************************************************
		**  Variables
		****************************************************************************************/		
		//SPI
		int* SPIHandles;											//SPI File Handles
		const char (*SPIPaths)[SPI_PATH_LEN];			//SPI Channel File Paths
		unsigned char numSPISpeeds;						//Number Of Supported SPI Speeds
		unsigned long* SPISupportedSpeeds;				//Supported SPI Clock Frequencies
		unsigned long* SPISetSpeeds;						//Set SPI Clock Frequencies
		unsigned char* SPIBitOrders;							//SPI Bit Orders
			
		//I2C
		int* I2CHandles;											//I2C File Handles
		const char (*I2CPaths)[I2C_PATH_LEN];			//I2C Channel File Paths
		
		//UART
		int* UartHandles;											//UART File Handles
		const char (*UartPaths)[UART_PATH_LEN];		//UART Channel File Paths
		unsigned char NumUartSpeeds;						///Number Of Support UART Buads
		unsigned long* UartSupportedSpeeds;				//Supported UART Bauds Frequencies
		unsigned long* UartSupportedSpeedsCodes;	//Supported UART Baud Divider Codes
		
		/****************************************************************************************
		**  Constructors
		****************************************************************************************/
		LINXRaspberryPi();
			
		/****************************************************************************************
		**  Functions
		****************************************************************************************/
		//Member Functions
		int GPIOExport(const unsigned char*  GPIOChans, const unsigned char numGPIOChans);
		int GPIOUnexport(const unsigned char*  GPIOChans, const unsigned char numGPIOChans);
		int GPIOSetDir(unsigned char pin, unsigned char mode);
		//Read
		int GPIOWrite(unsigned char pin, unsigned char val);
				
		//  Base Class Override Functions
		int digitalWrite(unsigned char numPins, unsigned char* pins, unsigned char* values);
		
		//SPI
		int SPIOpenMaster(unsigned char channel);
		int SPISetMode(unsigned char channel, unsigned char mode);
		int SPISetBitOrder(unsigned char channel, unsigned char mode);
		int SPISetSpeed(unsigned char channel, unsigned long speed, unsigned long* actualSpeed);
		int SPIWriteRead(unsigned char channel, unsigned char frameSize, unsigned char numFrames, unsigned char csChan, unsigned char csLL, unsigned char* sendBuffer, unsigned char* recBuffer);
		
		//I2C
		int I2COpenMaster(unsigned char channel);
		int I2CSetSpeed(unsigned char channel, unsigned long speed, unsigned long* actualSpeed);
		int I2CWrite(unsigned char channel, unsigned char slaveAddress, unsigned char eofConfig, unsigned char numBytes, unsigned char* sendBuffer);
		int I2CRead(unsigned char channel, unsigned char slaveAddress, unsigned char eofConfig, unsigned char numBytes, unsigned int timeout, unsigned char* recBuffer);
		int I2CClose(unsigned char channel);
		
		//UART
		int UartOpen(unsigned char channel, unsigned long baudRate, unsigned long* actualBaud);
		int UartSetBaudRate(unsigned char channel, unsigned long baudRate, unsigned long* actualBaud);
		int UartGetBytesAvailable(unsigned char channel, unsigned char *numBytes);
		int UartRead(unsigned char channel, unsigned char numBytes, unsigned char* recBuffer, unsigned char*numBytesRead);
		int UartWrite(unsigned char channel, unsigned char numBytes, unsigned char* sendBuffer);
		int UartClose(unsigned char channel);
		
	private:
		/****************************************************************************************
		**  Variables
		****************************************************************************************/		
		
		
		/****************************************************************************************
		**  Functions
		****************************************************************************************/
		
		
};


#endif //LINX_RASPBERRY_PI_H
