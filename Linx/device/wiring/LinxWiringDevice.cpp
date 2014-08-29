/****************************************************************************************
**  Includes
****************************************************************************************/	
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
//#include <Serial.h>

#include "../LinxDevice.h"
#include "LinxWiringDevice.h"

/****************************************************************************************
**  Variables
****************************************************************************************/		

/****************************************************************************************
**  Constructors / Destructors 
****************************************************************************************/
LinxWiringDevice::LinxWiringDevice( )
{
	//LINX API Version
	LinxApiMajor = 1;
	LinxApiMinor = 2;
	LinxApiSubminor = 0;	
}


/****************************************************************************************
**  Functions
****************************************************************************************/
unsigned long LinxWiringDevice::GetMilliSeconds()
{
	return millis();
}

unsigned long LinxWiringDevice::GetSeconds()
{
	return (millis() / 1000);
}
//--------------------------------------------------------DIGITAL-------------------------------------------------------

int LinxWiringDevice::DigitalWrite(unsigned char numPins, unsigned char* pins, unsigned char* values)
{
	for(int i=0; i<numPins; i++)
	{		
		pinMode(pins[i], OUTPUT);
		digitalWrite( pins[i], (values[i/8] >> i%8) & 0x01);
	}
	
	return 0;
}

//--------------------------------------------------------SPI-----------------------------------------------------------
int LinxWiringDevice::SpiOpenMaster(unsigned char channel)
{
	SPI.begin();
	return 0;
}

int LinxWiringDevice::SpiSetBitOrder(unsigned char channel, unsigned char bitOrder)
{
	SPI.setBitOrder(bitOrder);
	return 0;
}

int LinxWiringDevice::SpiSetMode(unsigned char channel, unsigned char mode)
{
	 SPI.setDataMode(mode);
	return 0;
}

int LinxWiringDevice::SpiSetSpeed(unsigned char channel, unsigned long speed, unsigned long* actualSpeed)
{
	int index = 0;
	//Loop Over All Supported SPI Speeds
	for(index=0; index < NumSpiSpeeds; index++)
	{
			
			if(speed < *(SpiSupportedSpeeds+index))
			{
				index = index - 1; //Use Fastest Speed Below Target Speed
				break;
			}
			//If Target Speed Is Higher Than Max Speed Use Max Speed	

			SPI.setClockDivider(*(SpiSupportedSpeeds+index));
	}
	return 0;
}

int LinxWiringDevice::SpiWriteRead(unsigned char channel, unsigned char frameSize, unsigned char numFrames, unsigned char csChan, unsigned char csLL, unsigned char* sendBuffer, unsigned char* recBuffer)
{
	//Set CS Pin As DO
	pinMode(csChan, OUTPUT);
	
	//Set CS Pin Before Starting SPI Transfer
	digitalWrite(csChan, (~csLL & 0x01) );  

	//Loop Over Frames
	for(int i=0; i<numFrames; i++)
	{
		//Loop Over Bytes In Frame
		for(int j=0; j<frameSize; j++)
		{
			//Transfer Data
			unsigned char byteNum = (i*frameSize) + j;
			recBuffer[byteNum] = SPI.transfer(sendBuffer[byteNum]);
		}
		
		//Frame Complete, Toggle CS
		digitalWrite(csChan, (csLL & 0x01) );
	}		
	return 0;
}

		
//--------------------------------------------------------I2C-----------------------------------------------------------
int LinxWiringDevice::I2cOpenMaster(unsigned char channel)
{
	if(*(I2cRefCount+channel) > 0)
	{
		//Channel Already Open, Increment Ref Count
		*(I2cRefCount+channel) = *(I2cRefCount+channel)+1;	
	}
	else
	{
		//Channel Not Yet Open, Open And Set Refcount = 1
		 Wire.begin();			//TODO ONLY SUPPORT ONE CHANNEL ATM
	}
	return 0;
}

int LinxWiringDevice::I2cSetSpeed(unsigned char channel, unsigned long speed, unsigned long* actualSpeed)
{
	return 0;
}

int LinxWiringDevice::I2cWrite(unsigned char channel, unsigned char slaveAddress, unsigned char eofConfig, unsigned char numBytes, unsigned char* sendBuffer)
{
		Wire.beginTransmission(slaveAddress);
		Wire.write(sendBuffer, numBytes);
		
		if(eofConfig == EOF_STOP)
		{
			Wire.endTransmission(true);
		}
		else if (eofConfig == EOF_RESTART)
		{
			Wire.endTransmission(false);
		}
		else
		{
			//EOF Not Supported, Stop Bus
			Wire.endTransmission(true);
			return LI2C_EOF;
		}
	
	return L_OK;
}

int LinxWiringDevice::I2cRead(unsigned char channel, unsigned char slaveAddress, unsigned char eofConfig, unsigned char numBytes, unsigned int timeout, unsigned char* recBuffer)
{
	if(eofConfig == EOF_STOP)
	{
		Wire.requestFrom(slaveAddress, numBytes, (uint8_t)1);
	}
	else if (eofConfig == EOF_RESTART)
	{
		Wire.requestFrom(slaveAddress, numBytes, 0);
	}
	else
	{
		//EOF Not Supported		
		return LI2C_EOF;
	}
	
	//Wait For Data, Potentially Timeout
	unsigned long tickCount = millis();
	while(Wire.available() < numBytes)
	{
		if( (millis() - tickCount) > timeout)
		{
			return LI2C_READ_FAIL;
		}
	}
	
	//Data Read, Read And Return
	for(int i=0; i<numBytes; i++)
	{
		*(recBuffer+i) = Wire.read();
	}
	
	return L_OK;
}

int LinxWiringDevice::I2cClose(unsigned char channel)
{
	//Function Not Supported
	return L_FUNCTION_NOT_SUPPORTED;
}

		
//--------------------------------------------------------UART----------------------------------------------------------
int LinxWiringDevice::UartOpen(unsigned char channel, unsigned long baudRate, unsigned long* actualBaud)
{
	int index = 0;
	for(index=0; index < NumUartSpeeds; index++)
	{
			
			if(baudRate < *(UartSupportedSpeeds+index))
			{
				index = index - 1; //Use Fastest Speed Below Target Speed
				break;
			}
			//If Target Speed Is Higher Than Max Speed Use Max Speed	
	}
	
	Serial.begin(*(UartSupportedSpeeds+index));
	*actualBaud = *(UartSupportedSpeeds+index);
	
	return L_OK;
}

int LinxWiringDevice::UartSetBaudRate(unsigned char channel, unsigned long baudRate, unsigned long* actualBaud)
{
	Serial.end();
	return UartOpen(channel, baudRate, actualBaud);
}

int LinxWiringDevice::UartGetBytesAvailable(unsigned char channel, unsigned char *numBytes)
{
	*numBytes = Serial.available();
	return 0;
}

int LinxWiringDevice::UartRead(unsigned char channel, unsigned char numBytes, unsigned char* recBuffer, unsigned char* numBytesRead)
{
	*numBytesRead = Serial.readBytes((char*)recBuffer, numBytes);
	
	if(*numBytesRead !=numBytes)
	{
		return LUART_READ_FAIL;
	}
	return 0;
}

int LinxWiringDevice::UartWrite(unsigned char channel, unsigned char numBytes, unsigned char* sendBuffer)
{
	unsigned char bytesSent = Serial.write(sendBuffer, numBytes);
	if(bytesSent != numBytes)
	{
		return LUART_WRITE_FAIL;
	}
	return 0;
}

int LinxWiringDevice::UartClose(unsigned char channel)
{
	Serial.end();
	return 0;
}
