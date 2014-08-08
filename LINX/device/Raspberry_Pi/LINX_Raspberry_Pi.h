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
		int* SPIHandles;									//SPI File Handles
		const char (*SPIPaths)[SPI_PATH_LEN];	//SPI Channel File Paths
		
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
		int SPIWriteRead(unsigned char channel, unsigned char frameSize, unsigned char csChan, unsigned char csLL, unsigned char* sendBuffer, unsigned char* recBuffer);
		
	private:
		/****************************************************************************************
		**  Variables
		****************************************************************************************/		
		
		
		/****************************************************************************************
		**  Functions
		****************************************************************************************/
		
		
};


#endif //LINX_RASPBERRY_PI_H
