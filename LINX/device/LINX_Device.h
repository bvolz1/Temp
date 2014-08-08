#ifndef LINX_DEVICE_H
#define LINX_DEVICE_H

/****************************************************************************************
**  Defines
****************************************************************************************/		
#define INPUT 0x00
#define OUTPUT 0x01

class LINXDevice
{
	public:	
		/****************************************************************************************
		**  Variables
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
		virtual int digitalWrite(unsigned char numPins, unsigned char* pins, unsigned char* values) = 0;
		
		//SPI
		virtual int SPIOpenMaster(unsigned char channel) = 0;
		virtual int SPISetMode(unsigned char channel, unsigned char mode) = 0;
		virtual int SPIWriteRead(unsigned char channel, unsigned char frameSize, unsigned char csChan, unsigned char csLL, unsigned char* sendBuffer, unsigned char* recBuffer) = 0;
				
	private:
		/****************************************************************************************
		**  Variables
		****************************************************************************************/		
				
				/****************************************************************************************
		**  Functions
		****************************************************************************************/
		
		
};


#endif //LINX_DEVICE_H
