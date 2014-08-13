#ifndef LINX_RASPBERRY_PI_H
#define LINX_RASPBERRY_PI_H

/****************************************************************************************
**  Includes
****************************************************************************************/		
#include <string>
#include "../LINX_Device.h"


#define SPI_PATH_LEN 64

/****************************************************************************************
**  Variables
****************************************************************************************/		

class LINXRaspberryPi : public LINXDevice
{
	public:	
		/****************************************************************************************
		**  Variables
		****************************************************************************************/		
		int* SPIHandles;											//SPI File Handles
		const char (*SPIPaths)[SPI_PATH_LEN];			//SPI Channel File Paths
		unsigned char numSPISpeeds;						//Number Of Supported SPI Speeds
		unsigned long* SPISupportedSpeeds;				//Supported SPI Clock Frequencies
		unsigned long* SPISetSpeeds;						//Set SPI Clock Frequencies
		unsigned char* SPIBitOrders;							//SPI Bit Orders
			
		
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
		SPIStatus SPIOpenMaster(unsigned char channel);
		SPIStatus SPISetMode(unsigned char channel, unsigned char mode);
		SPIStatus SPISetBitOrder(unsigned char channel, unsigned char mode);
		SPIStatus SPISetSpeed(unsigned char channel, unsigned long speed, unsigned long* actualSpeed);
		SPIStatus SPIWriteRead(unsigned char channel, unsigned char frameSize, unsigned char numFrames, unsigned char csChan, unsigned char csLL, unsigned char* sendBuffer, unsigned char* recBuffer);
		
	private:
		/****************************************************************************************
		**  Variables
		****************************************************************************************/		
		
		
		/****************************************************************************************
		**  Functions
		****************************************************************************************/
		
		
};


#endif //LINX_RASPBERRY_PI_H
