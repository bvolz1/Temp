/****************************************************************************************
**  Includes
****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../device/LinxDevice.h"

#include "LinxListener.h"
#include "LinxSerialListener.h"

/****************************************************************************************
**  Constructors
****************************************************************************************/
LinxSerialListener::LinxSerialListener()
{
	State = START;
	Interface = UART;
}

/****************************************************************************************
**  Functions
****************************************************************************************/
int LinxSerialListener::Start(LinxDevice &linxDev, unsigned char uartChan)
{
	ListenerChan = uartChan;
	unsigned long acutalBaud = 0;
	ListenerChan = uartChan;
	linxDev.UartOpen(ListenerChan, 9600, &acutalBaud);
	
	State = CONNECTED;
}

int LinxSerialListener::Connected(LinxDevice &linxDev)
{
	unsigned char bytesAvailable = 0;	
	
	//Check How Many Bytes Received, Need At Least 2 To Get SoF And Packet Size
	linxDev.UartGetBytesAvailable(ListenerChan, &bytesAvailable);
	
	if(bytesAvailable >= 2)
	{	
		//DEBUGDEBUG(">2 Bytes Available");
		//Check for valid SoF
		unsigned char bytesRead = 0;
		linxDev.UartRead(ListenerChan, 2, recBuffer, &bytesRead);
		printf("Received [%X] [%X]\n", recBuffer[0], recBuffer[1]);
		if(recBuffer[0] == 0xFF)
		{
			//SoF is valid. Check If Entire Packet Has Been Received
			linxDev.UartGetBytesAvailable(ListenerChan, &bytesAvailable);
		   
		   if(bytesAvailable < (recBuffer[1] - 2) )
			{
				//DEBUGDEBUG("Waiting for rest of packet\n");
				//Wait For More Bytes	
				int timeout = 100;
				while(bytesAvailable < (recBuffer[1] - 2) )
				{
					//DEBUGDEBUG("WAITING!!!");
					linxDev.UartGetBytesAvailable(ListenerChan, &bytesAvailable);
					printf("Received %d", bytesAvailable);
					if(timeout <= 0)
					{
						//Checksum Failed
						//DEBUGDEBUG("Timeout Waiting For Rest Of Packet\n");
						//Flush
						linxDev.UartGetBytesAvailable(ListenerChan, &bytesAvailable);
						linxDev.UartRead(ListenerChan, bytesAvailable, recBuffer, &bytesRead);
						return -1;
					}
					timeout--;
				}
			}
						
			//Full Packet Received
			//DEBUGDEBUG("Reading Rest Of Packet\n");
			linxDev.UartRead(ListenerChan, (recBuffer[1] - 2), (recBuffer+2), &bytesRead);
						
			//Full Packet Received - Compute Checksum - Process Packet If Checksum Passes
			if(ChecksumPassed(recBuffer))
			{
				//DEBUGDEBUG("Checksum Passed\n");
				//Process Packet
				ProcessCommand(recBuffer, sendBuffer, linxDev);
			
				//Send Response Packet      
				linxDev.UartWrite(ListenerChan, sendBuffer[1], sendBuffer);		
			}
			else
			{         
				//Checksum Failed
				//DEBUGDEBUG("Checksum Failed\n");
				//DEBUGDEBUGCMDPACKET(recBuffer);
				//Flush
				linxDev.UartGetBytesAvailable(ListenerChan, &bytesAvailable);
				linxDev.UartRead(ListenerChan, bytesAvailable, recBuffer, &bytesRead);
			}
		}
		else
		{
			//SoF Failed, Flush
			//DEBUGDEBUG("SoF Failed\n");
			//Flush
			linxDev.UartGetBytesAvailable(ListenerChan, &bytesAvailable);
			linxDev.UartRead(ListenerChan, bytesAvailable, recBuffer, &bytesRead); 
		}
	}
	
	return 0;
}

int LinxSerialListener::Close()
{
	return -1;
}

int LinxSerialListener::Exit()
{
	return -1;
}
