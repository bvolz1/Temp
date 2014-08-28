/****************************************************************************************
**  Includes
****************************************************************************************/		
#include <stdio.h>
#include <string> 
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sstream>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/i2c-dev.h>
#include <linux/spi/spidev.h>


#include <termios.h>		//UART Support

#include "../LinxDevice.h"
#include "LinxRaspberryPi.h"


/****************************************************************************************
**  Variables
****************************************************************************************/		

/****************************************************************************************
**  Constructors / Destructors 
****************************************************************************************/
LinxRaspberryPi::LinxRaspberryPi( )
{
	//-----All-----
	DeviceFamily = 0x04;
	
	//LINX API Version
	LinxApiMajor = 1;
	LinxApiMinor = 1;
	LinxApiSubminor = 0;	
}


/****************************************************************************************
**  Functions
****************************************************************************************/
unsigned long LinxRaspberryPi::GetMilliSeconds()
{
	timespec mTime;
	clock_gettime(CLOCK_MONOTONIC, &mTime);	
	return (mTime.tv_nsec / 1000000);
}

unsigned long LinxRaspberryPi::GetSeconds()
{
	timespec mTime;
	clock_gettime(CLOCK_MONOTONIC, &mTime);	
	return mTime.tv_sec;
}

void DebugPrint(char* message)
{
	printf(message);
	printf("\n");
}

void DebugPrintCmdPacket(unsigned char* packetBuffer)
{
	fprintf(stdout, "Received : ");		
		for(int i =0; i<packetBuffer[1]; i++)
		{
			fprintf(stdout, "[%X] ", packetBuffer[i]);
		}	
		fprintf(stdout, "\n");
}
void DebugPrintResPacket(unsigned char* packetBuffer)
{
	fprintf(stdout, "Replying With : ");
	for(int i=0; i<packetBuffer[1]; i++)
	{
		fprintf(stdout, "[%X] ", packetBuffer[i]);
	}	
	fprintf(stdout, "\n");
}

int LinxRaspberryPi::GpioExport (const unsigned char numGpioChans, const unsigned char*  gpioChans, int* digitalDirHandles, int* digitalValueHandles)
{
	DEBUG((char*)"Exporting GPIO");
	
	//Open Export File
	int exportFile = open("/sys/class/gpio/export", O_RDWR);	
	
	char buff[3];	
	
	//Export GPIO Pins And Open Handles To Direction And Value
	for(int i=0; i<numGpioChans; i++)
	{		
		//Export GPIO Pin
		snprintf(buff, 3, "%d",  gpioChans[i]);
		write(exportFile, buff, 3);
		
		//Open And Save GPIO Dir Handle
		char dirFilePath [40];
		snprintf(dirFilePath, 40, "/sys/class/gpio/gpio%d/direction", gpioChans[i]);
		int handle = open(dirFilePath, O_RDWR);
		if( handle > 0)
		{
			digitalDirHandles[i] = handle;
		}
		else
		{
			//Unable To Open Dir Handle
			printf("Unable To Open %s\n", dirFilePath);
		}
		
		
		//Open And Save GPIO Value Handle
		char valueFilePath [40];
		snprintf(valueFilePath, 40, "/sys/class/gpio/gpio%d/value", gpioChans[i]);
		digitalValueHandles[i] = open(valueFilePath, O_RDWR);
	}

	//Close Export File
	close(exportFile);		
	
	return 0;
}

int LinxRaspberryPi::GpioUnexport(const unsigned char*  gpioChans, const unsigned char numGpioChans)
{
	DEBUG((char*)"Unexporting GPIO");
	
	//Open Unexport File
	int unexportFile = open("/sys/class/gpio/unexport", O_RDWR);	
	
	char buff[3];	
	
	//Export GPIO Pins
	for(int i=0; i<numGpioChans; i++)
	{
		snprintf(buff, 3, "%d",  gpioChans[i]);
		write(unexportFile, buff, 3);
	}
	
	return 0;
}

int LinxRaspberryPi::GpioSetDir(unsigned char pin, unsigned char mode)
{
	DEBUG((char*)"RPI GPIO Set Dir");
	
	int pinIndex = GetDigitalChanIndex(pin);
	
	if(pinIndex < 0)
	{
		return LDIGITAL_PIN_DNE;
	}
	else
	{
		int dirHandle = DigitalDirHandles[pinIndex];
		
		if(mode == INPUT)
		{
			write(dirHandle, "in", 2);
		}
		else if (mode == OUTPUT)
		{
			write(dirHandle, "out", 3);
		}
		else
		{
			//TODO ERROR
		}
	}
		
	return 0;
}

int LinxRaspberryPi::GpioWrite(unsigned char pin, unsigned char val)
{
	DEBUG((char*)"RPI GPIO Write");
	
	int pinIndex = GetDigitalChanIndex(pin);
	
	if(pinIndex < 0)
	{
		return LDIGITAL_PIN_DNE;
	}
	else
	{
		int valueHandle = DigitalValueHandles[pinIndex];
		
		if(val == HIGH)
		{
			write(valueHandle, "1\00", 2);
		}
		else if (val == LOW)
		{
			write(valueHandle, "0\00", 2);
		}
		else
		{
			//TODO ERROR
		}
	}
		
	return 0;
}

int LinxRaspberryPi::DigitalWrite(unsigned char numPins, unsigned char* pins, unsigned char* values)
{
	for(int i=0; i<numPins; i++)
	{		
		GpioSetDir(pins[i], 1);
		GpioWrite( pins[i], (values[i/8] >> i%8) & 0x01);
	}
	
	return 0;
}

//----------SPI

int LinxRaspberryPi::SpiOpenMaster(unsigned char channel)
{
	//Channel Checking Is Done On Farther Up The Stack, So Just Open It
	int handle = open(SpiPaths[channel], O_RDWR);
	if (handle < 0)
	{
		DEBUG((char*)"Failed To Open SPI Channel");
		return  L_UNKNOWN_ERROR;
	}
	else
	{
		//Default To Mode 0 With No CS (We'll Use GPIO When Performing Write)
		unsigned long spi_Mode = SPI_NO_CS | SPI_MODE_0;
		int retVal = ioctl(handle, SPI_IOC_WR_MODE, &spi_Mode);		
		SpiHandles[channel] = handle;
		return L_OK;
	}
}

int LinxRaspberryPi::SpiSetBitOrder(unsigned char channel, unsigned char bitOrder)
{
	//Store Bit Order.  This Will Be Used During Write
	*(SpiBitOrders+channel) = bitOrder;
}

int LinxRaspberryPi::SpiSetMode(unsigned char channel, unsigned char mode)	
{
	unsigned long spi_Mode = SPI_NO_CS | (unsigned long) mode;
	int retVal = ioctl(SpiHandles[channel], SPI_IOC_WR_MODE, &spi_Mode);
	if(retVal < 0)
	{
		DEBUG((char*)"Failed To Set SPI Mode");
		return  L_UNKNOWN_ERROR;
	}
	else
	{
		return L_OK;
	}	
}

int LinxRaspberryPi::SpiSetSpeed(unsigned char channel, unsigned long speed, unsigned long* actualSpeed)
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
	}
	*(SpiSetSpeeds+channel) = *(SpiSupportedSpeeds+index);
	*actualSpeed = *(SpiSupportedSpeeds+index);
	return L_OK;
}

int LinxRaspberryPi::SpiWriteRead(unsigned char channel, unsigned char frameSize, unsigned char numFrames, unsigned char csChan, unsigned char csLL, unsigned char* sendBuffer, unsigned char* recBuffer)
{
	unsigned char nextByte = 0;	//First Byte Of Next SPI Frame	
	
	//SPI Hardware Only Supports MSb First Transfer.  If  Configured for LSb First Reverse Bits In Software
	if( *(SpiBitOrders+channel) == LSBFIRST )
	{
		for(int i=0; i< frameSize*numFrames; i++)
		{			
			sendBuffer[i] = ReverseBits(sendBuffer[i]);
		}
	}
	
	struct spi_ioc_transfer transfer;
	
	//Set CS As Output And Make Sure GPIO CS Starts Idle	
	GpioSetDir(csChan, OUTPUT);	
	GpioWrite(csChan, (~csLL & 0x01) );
	
	for(int i=0; i< numFrames; i++)
	{
		//Setup Transfer
		transfer.tx_buf = (unsigned long)(sendBuffer+nextByte);
		transfer.rx_buf = (unsigned long)(recBuffer+nextByte);
		transfer.len = frameSize;
		transfer.delay_usecs = 0;
		transfer.speed_hz = *(SpiSetSpeeds+channel) * 2;
		//transfer.speed_hz = 3000000;
		transfer.bits_per_word = 8;
	
		//CS Active
		GpioWrite(csChan, csLL);
		
		//Transfer Data
		int retVal = ioctl(SpiHandles[channel], SPI_IOC_MESSAGE(1), &transfer);
		
		//CS Idle
		GpioWrite(csChan, (~csLL & 0x01) );
		
		if (retVal < 1)
		{
			DEBUG((char*)"Failed To Send SPI Data");
			return  L_UNKNOWN_ERROR;
		}
	}	
	
	return L_OK;
}

//----------I2C----------//
int LinxRaspberryPi::I2cOpenMaster(unsigned char channel)
{
	int handle = open(I2cPaths[channel], O_RDWR);
	if (handle < 0)
	{
		DEBUG((char*)"Failed To Open I2C Channel");
		return  LI2C_OPEN_FAIL;
	}
	else
	{
		I2cHandles[channel] = handle;
	}
	return L_OK;
}

int LinxRaspberryPi::I2cSetSpeed(unsigned char channel, unsigned long speed, unsigned long* actualSpeed)
{
	return  L_FUNCTION_NOT_SUPPORTED;
}

int LinxRaspberryPi::I2cWrite(unsigned char channel, unsigned char slaveAddress, unsigned char eofConfig, unsigned char numBytes, unsigned char* sendBuffer)
{
	//Check EOF - Currently Only Support 0x00
	if(eofConfig != EOF_STOP)
	{
		return LI2C_EOF;	
	}
	
	//Set Slave Address
	if (ioctl(I2cHandles[channel], I2C_SLAVE, slaveAddress) < 0) 
	{
		//Failed To Set Slave Address
		return LI2C_SADDR;
	}
		
	//Write Data
	if(write(I2cHandles[channel], sendBuffer, numBytes) != numBytes)
	{
		return LI2C_WRITE_FAIL;
	}
	
	return L_OK;
}

int LinxRaspberryPi::I2cRead(unsigned char channel, unsigned char slaveAddress, unsigned char eofConfig, unsigned char numBytes, unsigned int timeout, unsigned char* recBuffer)
{
	//Check EOF - Currently Only Support 0x00
	if(eofConfig != EOF_STOP)
	{
		return LI2C_EOF;	
	}
	
	//Set Slave Address
	if (ioctl(I2cHandles[channel], I2C_SLAVE, slaveAddress) < 0) 
	{
		//Failed To Set Slave Address
		return LI2C_SADDR;
	}
	
	if(read(I2cHandles[channel], recBuffer, numBytes) < numBytes)
	{
		return LI2C_READ_FAIL;	
	}
	return L_OK;
}

int LinxRaspberryPi::I2cClose(unsigned char channel)
{
	//Close I2C Channel
	if(close(I2cHandles[channel]) < 0)
	{
		return LI2C_CLOSE_FAIL;
	}
	
	return L_OK;
}

//UART
int LinxRaspberryPi::UartOpen(unsigned char channel, unsigned long baudRate, unsigned long* actualBaud)
{
	//Open UART	
	int handle = open(UartPaths[channel],  O_RDWR | O_NDELAY);
	
	if (handle < 0)
	{
		DEBUG((char*)"Failed To Open UART Channel");
		return  LUART_OPEN_FAIL;
	}	
	else
	{
		UartHandles[channel] = handle;
	}
	
	UartSetBaudRate(channel, baudRate, actualBaud);
	
	return L_OK;
}

int LinxRaspberryPi::UartSetBaudRate(unsigned char channel, unsigned long baudRate , unsigned long* actualBaud)
{
	
	//Get Closest Support Baud Rate Without Going Over
	
	//Loop Over All Supported SPI Speeds
	int index = 0;
	for(index=0; index < NumUartSpeeds; index++)
	{
			
			if(baudRate < *(UartSupportedSpeeds+index))
			{
				index = index - 1; //Use Fastest Baud Less Or Equal To Target Baud
				break;
			}
			//If Target Baud Is Higher Than Max Baud Use Max Baud			
	}
	
	//Store Actual Baud Used
	*actualBaud = (unsigned long) *(UartSupportedSpeeds+index);
	printf("Baud = %d\n", *(UartSupportedSpeeds+index));
	
	//Set Baud Rate
	struct termios options;	
	tcgetattr(UartHandles[channel], &options);
	
	options.c_cflag = *(UartSupportedSpeedsCodes+index) | CS8 | CLOCAL | CREAD;
	options.c_iflag = IGNPAR;
	options.c_oflag = 0;
	options.c_lflag = 0;
	
	tcflush(UartHandles[channel], TCIFLUSH);	
	tcsetattr(UartHandles[channel], TCSANOW, &options);
	
	return  L_OK;
}

int LinxRaspberryPi::UartGetBytesAvailable(unsigned char channel, unsigned char *numBytes)
{
	int bytesAtPort = -1;
	ioctl(UartHandles[channel], FIONREAD, &bytesAtPort);
	
	if(bytesAtPort < 0)
	{
		return LUART_AVAILABLE_FAIL;
	}
	else
	{
		*numBytes = (unsigned char) bytesAtPort;
	}
	return  L_OK;
}

int LinxRaspberryPi::UartRead(unsigned char channel, unsigned char numBytes, unsigned char* recBuffer, unsigned char* numBytesRead)
{
	//Check If Enough Bytes Are Available
	unsigned char bytesAvailable = -1;
	UartGetBytesAvailable(channel, &bytesAvailable);
	
	if(bytesAvailable >= numBytes)
	{
		//Read Bytes From Input Buffer
		int bytesRead = read(UartHandles[channel], recBuffer, numBytes);
		*numBytesRead = (unsigned char) bytesRead;
		
		if(bytesRead != numBytes)
		{
			return LUART_READ_FAIL;
		}		
	}
	return  L_OK;
}

int LinxRaspberryPi::UartWrite(unsigned char channel, unsigned char numBytes, unsigned char* sendBuffer)
{
	
	//debug
	printf("\n");
	for(int i=0; i< numBytes; i++)
	{
		printf("%c", *(sendBuffer+i));
	}
		printf("\n");
	
	
	
	int bytesSent = write(UartHandles[channel], sendBuffer, numBytes);	
	if(bytesSent != numBytes)
	{
		return LUART_WRITE_FAIL;
	}
	return  L_OK;
}

int LinxRaspberryPi::UartClose(unsigned char channel)
{
	//Close UART Channel, Return OK or Error
	if (close(UartHandles[channel]) < 0)
	{
		return LUART_CLOSE_FAIL;
	}
	return  L_OK;
}

int LinxRaspberryPi::GetDigitalChanIndex(unsigned char chanNum)
{
	for(int i=0; i< NumDigitalChans; i++)
	{
		if(DigitalChans[i] == chanNum)
		{
			return i;
		}		
	}
	return -1;
}