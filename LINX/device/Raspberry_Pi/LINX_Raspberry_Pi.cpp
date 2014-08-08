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

int LINXRaspberryPi::SPIOpenMaster(unsigned char channel)
{
	fprintf(stdout, "Trying to Open = %s\n", SPIPaths[0]);
	//Channel Checking Is Done On Farther Up The Stack, So Just Open It
	int handle = open(SPIPaths[channel], O_RDWR);
	if (handle < 0)
	{
		DEBUG("Failed To Open SPI Channel");
		return -1;
	}
	else
	{
		SPIHandles[channel] = handle;
		return 0;
	}
}

int LINXRaspberryPi::SPISetMode(unsigned char channel, unsigned char mode)	
{
	
	int retVal = ioctl(SPIHandles[channel], SPI_IOC_WR_MODE, mode);
	if(retVal < 0)
	{
		DEBUG("Failed To Set SPI Mode");
		return -1;
	}
	else
	{
		return 0;
	}	
}

int LINXRaspberryPi::SPIWriteRead(unsigned char channel, unsigned char frameSize, unsigned char csChan, unsigned char csLL, unsigned char* sendBuffer, unsigned char* recBuffer)
{
	struct spi_ioc_transfer transfer = {
		transfer.tx_buf = (unsigned long) sendBuffer,
		transfer.rx_buf = (unsigned long)recBuffer,
		transfer.len = frameSize,
		transfer.delay_usecs = 0,
		transfer.speed_hz = 500000,
		transfer.bits_per_word = 8,
	};
	
	int retVal = ioctl(SPIHandles[channel], SPI_IOC_MESSAGE(1), &transfer);
	if (retVal < 1)
	{
		DEBUG("Failed To Send SPI Data");
		fprintf(stdout, "error = %d\n", retVal);
		return -1;
	}
	else
	{
		return 0;
	}
	

}