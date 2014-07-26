 


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

#include "LINX_Config.h"
#include "LINX_Common.h"
#include "LINX_Networking.h"
#include "device/LINX_Device.h"

#include "device/Raspberry_Pi/LINX_Raspberry_Pi.h"

/****************************************************************************************
** Variables
****************************************************************************************/
TCPServer LINXServer;
LINXRaspberryPi LINXDev;

int main(int argc, char *argv[])
{

	debug_Println("Starting LVH LINX");
	
	//Start LINX TCP Server
	
	
	while(1)
	{	
	
		//TCP Server State Machine
		switch(LINXServer.state)
		{
			case START:
				debug_Println("Start State");
				LINXServer.begin(6999);
				break;
			
			case LISTENING:
				debug_Println("Listening State");
				LINXServer.acceptConnection();
				break;					
				
			case CONNECTED:
				debug_Println("Connected State");
				LINXServer.processPackets(LINXDev);
				break;

			case RESTART:
				debug_Println("Restarting LINX Server");
				LINXServer.stop();
				LINXServer.state = START;
				break;					
				
			case EXIT:
				debug_Println("Exit State");
				LINXServer.stop();
				exit(-1);
				break;				
		}

	}
	
}