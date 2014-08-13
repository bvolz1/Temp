#ifndef LINX_DEVICE_H
#define LINX_DEVICE_H

/****************************************************************************************
**  Includes
****************************************************************************************/		


/****************************************************************************************
**  Defines
****************************************************************************************/		
#define INPUT 0x00
#define OUTPUT 0x01

#define LSBFIRST 0
#define MSBFIRST 1

/****************************************************************************************
**  Typedefs
****************************************************************************************/		
typedef enum SPIStatus{LSPI_OK, LSPI_UNKNOWN_ERROR}SPIStatus;

class LINXDevice
{
	public:	
		/****************************************************************************************
		**  Member Variables
		****************************************************************************************/				
		
		//Device ID
		unsigned char deviceFamily;
		unsigned char deviceID;
		unsigned char deviceNameLen;
		const unsigned char* deviceName;
		
		//LINX API Version
		unsigned char linxAPIMajor;
		unsigned char linxAPIMinor;
		unsigned char linxAPISubminor;
		
		//----Peripherals----
		
		//DIO		
		unsigned char numDIOChans;
		const unsigned char*  DIOChans;
		
		//AI
		unsigned char numAIChans;
		const unsigned char* AIChans;
		unsigned char AIResolution;
		unsigned long AIRef;
		
		//AO
		unsigned char numAOChans;
		const unsigned char* AOChans;
		
		//PWM
		unsigned char numPWMChans;
		const unsigned char* PWMChans;
		
		//QE
		unsigned char numQEChans;
		const unsigned char* QEChans;
		
		//UART
		unsigned char numUARTChans;
		const unsigned char* UARTChans;
		
		//I2C
		unsigned char numI2CChans;
		const unsigned char* I2CChans;
		
		//SPI
		unsigned char numSPIChans;
		const unsigned char* SPIChans;
		
		//CAN
		unsigned char numCANChans;
		const unsigned char* CANChans;
		
		/****************************************************************************************
		**  Constructors
		****************************************************************************************/
		LINXDevice();
			
		/****************************************************************************************
		**  Functions
		****************************************************************************************/
		//DIO
		virtual int digitalWrite(unsigned char numPins, unsigned char* pins, unsigned char* values) = 0;
		
		//SPI
		virtual SPIStatus SPIOpenMaster(unsigned char channel) = 0;
		virtual SPIStatus SPISetBitOrder(unsigned char channel, unsigned char bitOrder) = 0;
		virtual SPIStatus SPISetMode(unsigned char channel, unsigned char mode) = 0;
		virtual SPIStatus SPISetSpeed(unsigned char channel, unsigned long speed, unsigned long* actualSpeed) = 0;
		virtual SPIStatus SPIWriteRead(unsigned char channel, unsigned char frameSize, unsigned char numFrames, unsigned char csChan, unsigned char csLL, unsigned char* sendBuffer, unsigned char* recBuffer) = 0;
		
		//General - 
		unsigned char reverseBits(unsigned char b);
				
	private:
		/****************************************************************************************
		**  Variables
		****************************************************************************************/		
				
		/****************************************************************************************
		**  Functions
		****************************************************************************************/
};
#endif //LINX_DEVICE_H
