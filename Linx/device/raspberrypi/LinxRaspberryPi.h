#ifndef LINX_RASPBERRY_PI_H
#define LINX_RASPBERRY_PI_H

/****************************************************************************************
**  Includes
****************************************************************************************/		
#include <string>
#include "../LinxDevice.h"

#define DIGITAL_PIN_LEN 3
#define SPI_PATH_LEN 64
#define I2C_PATH_LEN 64
#define UART_PATH_LEN 64

/****************************************************************************************
**  Variables
****************************************************************************************/		

class LinxRaspberryPi : public LinxDevice
{
	public:	
		/****************************************************************************************
		**  Variables
		****************************************************************************************/		
		//DIO
		//unsigned char NumDigitalChans;									//Number Of Digital Channels
		int* DigitalDirHandles;													//File Handles For Digital Pin Directions
		int* DigitalValueHandles;												//File Handles For Digital Pin Values
		const char (*DigitalPinNames)[DIGITAL_PIN_LEN];			//SPI Channel Names (Chars)		
		
		//SPI
		int* SpiHandles;												//SPI File Handles
		const char (*SpiPaths)[SPI_PATH_LEN];			//SPI Channel File Paths
		unsigned char NumSpiSpeeds;						//Number Of Supported SPI Speeds
		unsigned long* SpiSupportedSpeeds;				//Supported SPI Clock Frequencies
		unsigned long* SpiSetSpeeds;						//Set SPI Clock Frequencies
		unsigned char* SpiBitOrders;							//SPI Bit Orders
			
		//I2C
		int* I2cHandles;												//I2C File Handles
		const char (*I2cPaths)[I2C_PATH_LEN];			//I2C Channel File Paths
		
		//UART
		int* UartHandles;											//UART File Handles
		const char (*UartPaths)[UART_PATH_LEN];		//UART Channel File Paths
		unsigned char NumUartSpeeds;						///Number Of Support UART Buads
		unsigned long* UartSupportedSpeeds;				//Supported UART Bauds Frequencies
		unsigned long* UartSupportedSpeedsCodes;	//Supported UART Baud Divider Codes
		
		/****************************************************************************************
		**  Constructors
		****************************************************************************************/
		LinxRaspberryPi();
			
		/****************************************************************************************
		**  Functions
		****************************************************************************************/
		//Member Functions
		int GpioExport(const unsigned char numGpioChans, const unsigned char*  gpioChans, int* digitalDirHandles, int* digitalValueHandles);
		int GpioUnexport(const unsigned char*  GPIOChans, const unsigned char numGPIOChans);
		int GpioSetDir(unsigned char pin, unsigned char mode);
		//Read
		int GpioWrite(unsigned char pin, unsigned char val);
				
		//  Base Class Override Functions
		int DigitalWrite(unsigned char numPins, unsigned char* pins, unsigned char* values);
		
		//SPI
		int SpiOpenMaster(unsigned char channel);
		int SpiSetMode(unsigned char channel, unsigned char mode);
		int SpiSetBitOrder(unsigned char channel, unsigned char mode);
		int SpiSetSpeed(unsigned char channel, unsigned long speed, unsigned long* actualSpeed);
		int SpiWriteRead(unsigned char channel, unsigned char frameSize, unsigned char numFrames, unsigned char csChan, unsigned char csLL, unsigned char* sendBuffer, unsigned char* recBuffer);
		
		//I2C
		int I2cOpenMaster(unsigned char channel);
		int I2cSetSpeed(unsigned char channel, unsigned long speed, unsigned long* actualSpeed);
		int I2cWrite(unsigned char channel, unsigned char slaveAddress, unsigned char eofConfig, unsigned char numBytes, unsigned char* sendBuffer);
		int I2cRead(unsigned char channel, unsigned char slaveAddress, unsigned char eofConfig, unsigned char numBytes, unsigned int timeout, unsigned char* recBuffer);
		int I2cClose(unsigned char channel);
		
		//UART
		int UartOpen(unsigned char channel, unsigned long baudRate, unsigned long* actualBaud);
		int UartSetBaudRate(unsigned char channel, unsigned long baudRate, unsigned long* actualBaud);
		int UartGetBytesAvailable(unsigned char channel, unsigned char *numBytes);
		int UartRead(unsigned char channel, unsigned char numBytes, unsigned char* recBuffer, unsigned char*numBytesRead);
		int UartWrite(unsigned char channel, unsigned char numBytes, unsigned char* sendBuffer);
		int UartClose(unsigned char channel);
		
	protected:
		/****************************************************************************************
		**  Variables
		****************************************************************************************/		
		int GetDigitalChanIndex(unsigned char chanNum);
		
		/****************************************************************************************
		**  Functions
		****************************************************************************************/
		
		
};


#endif //LINX_RASPBERRY_PI_H
