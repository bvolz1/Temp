#ifndef LINX_DEVICE_H
#define LINX_DEVICE_H

/****************************************************************************************
**  Includes
****************************************************************************************/		


/****************************************************************************************
**  Defines
****************************************************************************************/		
//GPIO
#define INPUT 0x00
#define OUTPUT 0x01

//SPI
#define LSBFIRST 0
#define MSBFIRST 1

//I2C
#define EOF_STOP 0
#define EOF_RESTART 1
#define EOF_RESTART_NOSTOP 2
#define EOF_NOSTOP 3

#define L_STATUS_COMMON 2

/****************************************************************************************
**  Typedefs
****************************************************************************************/		
typedef enum SPIStatus
{
	
}SPIStatus;

typedef enum I2CStatus
{
	LI2C_SADDR=128, 
	LI2C_EOF, 
	LI2C_WRITE_FAIL, 
	LI2C_CLOSE_FAIL
}I2CStatus;

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
		virtual int SPIOpenMaster(unsigned char channel) = 0;
		virtual int SPISetBitOrder(unsigned char channel, unsigned char bitOrder) = 0;
		virtual int SPISetMode(unsigned char channel, unsigned char mode) = 0;
		virtual int SPISetSpeed(unsigned char channel, unsigned long speed, unsigned long* actualSpeed) = 0;
		virtual int SPIWriteRead(unsigned char channel, unsigned char frameSize, unsigned char numFrames, unsigned char csChan, unsigned char csLL, unsigned char* sendBuffer, unsigned char* recBuffer) = 0;
		
		//I2C
		virtual int I2COpenMaster(unsigned char channel) = 0;
		virtual int I2CSetSpeed(unsigned char channel, unsigned long speed, unsigned long* actualSpeed) = 0;
		virtual int I2CWrite(unsigned char channel, unsigned char slaveAddress, unsigned char eofConfig, unsigned char numBytes, unsigned char* sendBuffer) = 0;
		virtual int I2CRead(unsigned char channel, unsigned char numBytes, unsigned char* recBuffer) = 0;
		virtual int I2CClose(unsigned char channel) = 0;
		
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
