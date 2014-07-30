 /****************************************************************************************
**  Defines
****************************************************************************************/

 /****************************************************************************************
**  Includes
****************************************************************************************/
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#include "LINX_Common.h"
#include "LINX_Networking.h"
#include "device/LINX_Device.h"

#include "device/Raspberry_Pi/LINX_Raspberry_Pi_B.h"

/****************************************************************************************
** Variables
****************************************************************************************/
TCPServer LINXServer;

LINXRaspberryPi_B LINXDev;	

int main(int argc, char *argv[])
{


	
	DEBUG("\nStarting LVH LINX On");
	//Start LINX TCP Server	
	while(1)
	{	
	
		//TCP Server State Machine
		switch(LINXServer.state)
		{
			case START:
				DEBUG("Start State");
				LINXServer.begin(6999);
				break;
			
			case LISTENING:
				DEBUG("Listening State");
				LINXServer.acceptConnection();
				break;					
				
			case CONNECTED:
				DEBUG("Connected State");
				LINXServer.processPackets(LINXDev);
				break;

			case RESTART:
				DEBUG("Restarting LINX Server");
				LINXServer.stop();
				LINXServer.state = START;
				break;					
				
			case EXIT:
				DEBUG("Exit State\n");
				LINXServer.stop();
				exit(-1);
				break;				
		}

	}
	
}