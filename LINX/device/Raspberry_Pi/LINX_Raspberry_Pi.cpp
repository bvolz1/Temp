/****************************************************************************************
**  Includes
****************************************************************************************/		
#include <stdio.h>
#include <string> 
#include <fcntl.h>
#include <sstream>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

#include "../../LINX_Common.h"
#include "../LINX_Device.h"
#include "LINX_Raspberry_Pi.h"


/****************************************************************************************
**  Variables
****************************************************************************************/		

/****************************************************************************************
**  Constructors / Destructors 
****************************************************************************************/
LINXRaspberryPi::LINXRaspberryPi( )
{
	//-----All-----
	deviceFamily = 0x04;
	
	//LINX API Version
	linxAPIMajor = 1;
	linxAPIMinor = 1;
	linxAPISubminor = 0;	
}


/****************************************************************************************
**  Functions
****************************************************************************************/
int LINXRaspberryPi::GPIOExport (const unsigned char*  GPIOChans, const unsigned char numGPIOChans)
{
	DEBUG("Exporting GPIO");
	
	//Export File
	FILE * exportFile;	
		
	//Export GPIO Pins
	for(int i=0; i<numGPIOChans; i++)
	{
		//Open Export File
		exportFile = fopen("/sys/class/gpio/export", "w");
		
		fprintf(exportFile, "%u", GPIOChans[i]);		
		
		//Close Export File
		fclose(exportFile);		
	}
	
	return 0;
}

int LINXRaspberryPi::GPIOUnexport(const unsigned char*  GPIOChans, const unsigned char numGPIOChans)
{
	DEBUG("Unexporting GPIO");
	
	//Unexport File
	FILE * unexportFile;

	//Export GPIO Pins
	for(int i=0; i<numGPIOChans; i++)
	{
		//Open Unexport File
		unexportFile = fopen("/sys/class/gpio/unexport", "w");
		
		fprintf(unexportFile, "%u", GPIOChans[i]);			
		
		//Close Unexport File
		fclose(unexportFile);
	}
	
	return 0;
}

int LINXRaspberryPi::GPIOSetDir(unsigned char pin, unsigned char mode)
{
	DEBUG("RPI GPIO Set Dir");
	
	//GPIO Direction File Handle
	FILE *dirFile;
	
	char filePath [40];
	snprintf(filePath, 40, "/sys/class/gpio/gpio%d/direction", pin );
	dirFile = fopen(filePath, "w");
	
	if(dirFile == NULL)
	{
		printf("Failed To Open %s\n", filePath);
	}
	else
	{	
		if(mode == INPUT)
		{
			fprintf(dirFile, "in");
			fclose(dirFile);
				
		}
		else if (mode == OUTPUT)
		{
			fprintf(dirFile, "out");
			fclose(dirFile);			
		}
		else
		{
			//TODO ERROR
		}			
	}
	
	return 0;
	
}

int LINXRaspberryPi::GPIOWrite(unsigned char pin, unsigned char val)
{
	DEBUG("RPI GPIO Write");
	
	//GPIO Value File Handle
	FILE *valFile;
	
	//Build GPIO Value Path And Open
	char filePath [40];
	snprintf(filePath, 40, "/sys/class/gpio/gpio%d/value", pin );
	valFile = fopen(filePath, "w");
	
	//Write Value
	fprintf(valFile, "%u", val);	
		
	//Close GPIO Value File
	fclose(valFile);
		
	return 0;
}

int LINXRaspberryPi::digitalWrite(unsigned char numPins, unsigned char* pins, unsigned char* values)
{
	DEBUG("Digital Write At Pi Level");		
	
	for(int i=0; i<numPins; i++)
	{		
		GPIOSetDir(pins[i], 1);
		GPIOWrite( pins[i], (values[i/8] >> i%8) & 0x01);
	}
	
	return 0;
}

//----------SPI

SPIStatus LINXRaspberryPi::SPIOpenMaster(unsigned char channel)
{
	//Channel Checking Is Done On Farther Up The Stack, So Just Open It
	int handle = open(SPIPaths[channel], O_RDWR);
	if (handle < 0)
	{
		DEBUG("Failed To Open SPI Channel");
		return  LSPI_UNKNOWN_ERROR;
	}
	else
	{
		//Default To Mode 0 With No CS (We'll Use GPIO When Performing Write)
		unsigned long spi_Mode = SPI_NO_CS | SPI_MODE_0;
		int retVal = ioctl(handle, SPI_IOC_WR_MODE, &spi_Mode);		
		SPIHandles[channel] = handle;
		return LSPI_OK;
	}
}

SPIStatus LINXRaspberryPi::SPISetBitOrder(unsigned char channel, unsigned char bitOrder)
{
	//Store Bit Order.  This Will Be Used During Write
	*(SPIBitOrders+channel) = bitOrder;
}

SPIStatus LINXRaspberryPi::SPISetMode(unsigned char channel, unsigned char mode)	
{
	unsigned long spi_Mode = SPI_NO_CS | (unsigned long) mode;
	int retVal = ioctl(SPIHandles[channel], SPI_IOC_WR_MODE, &spi_Mode);
	if(retVal < 0)
	{
		DEBUG("Failed To Set SPI Mode");
		return  LSPI_UNKNOWN_ERROR;
	}
	else
	{
		return LSPI_OK;
	}	
}

SPIStatus LINXRaspberryPi::SPISetSpeed(unsigned char channel, unsigned long speed, unsigned long* actualSpeed)
{

	printf("Target Clock Freq = %d\n", speed);
	int index = 0;
	//Loop Over All Supported SPI Speeds
	for(index=0; index < numSPISpeeds; index++)
	{
			
			if(speed < *(SPISupportedSpeeds+index))
			{
				index = index - 1; //Use Fastest Speed Below Target Speed
				break;
			}
			//If Target Speed Is Higher Than Max Speed Use Max Speed
			
	}
	printf("Actual Clock Freq = %d\n", *(SPISupportedSpeeds+index));
	*(SPISetSpeeds+channel) = *(SPISupportedSpeeds+index);
	*actualSpeed = *(SPISupportedSpeeds+index);
	return LSPI_OK;
}

SPIStatus LINXRaspberryPi::SPIWriteRead(unsigned char channel, unsigned char frameSize, unsigned char numFrames, unsigned char csChan, unsigned char csLL, unsigned char* sendBuffer, unsigned char* recBuffer)
{
	unsigned char nextByte = 0;	//First Byte Of Next SPI Frame	
	
	//SPI Hardware Only Supports MSb First Transfer.  If  Configured for LSb First Reverse Bits In Software
	if( *(SPIBitOrders+channel) == LSBFIRST )
	{
		for(int i=0; i< frameSize*numFrames; i++)
		{			
			printf("Flipping %X to ", sendBuffer[i]);
			sendBuffer[i] = reverseBits(sendBuffer[i]); 
			printf("%X\n", sendBuffer[i]);
		}
	}
	
	struct spi_ioc_transfer transfer;
	
	//Set CS As Output And Make Sure GPIO CS Starts Idle	
	GPIOSetDir(csChan, OUTPUT);	
	GPIOWrite(csChan, (~csLL & 0x01) );
	
	for(int i=0; i< numFrames; i++)
	{
		//Setup Transfer
		transfer.tx_buf = (unsigned long)(sendBuffer+nextByte);
		transfer.rx_buf = (unsigned long)(recBuffer+nextByte);
		transfer.len = frameSize;
		transfer.delay_usecs = 0;
		transfer.speed_hz = *(SPISupportedSpeeds+channel);
		transfer.bits_per_word = 8;
	
		//CS Active
		GPIOWrite(csChan, csLL);
		
		//Transfer Data
		int retVal = ioctl(SPIHandles[channel], SPI_IOC_MESSAGE(1), &transfer);
		
		//CS Idle
		GPIOWrite(csChan, (~csLL & 0x01) );
		
		if (retVal < 1)
		{
			DEBUG("Failed To Send SPI Data");
			return  LSPI_UNKNOWN_ERROR;
		}
	}	
	
	return LSPI_OK;
}