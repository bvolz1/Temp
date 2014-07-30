#ifndef LINX_DEVICE_H
#define LINX_DEVICE_H

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
		
		//Digital I/O
				
	private:
		/****************************************************************************************
		**  Variables
		****************************************************************************************/		
				
		
		/****************************************************************************************
		**  Functions
		****************************************************************************************/
		
		
};


#endif //LINX_DEVICE_H
