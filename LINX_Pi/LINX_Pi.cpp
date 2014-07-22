


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

/****************************************************************************************
** Variables
****************************************************************************************/
TCPServer LINXServer;

int main(int argc, char *argv[])
{

	debugPrintln("Starting LVH LINX");
	
	//Start LINX TCP Server
	
	
	while(1)
	{
		//TCP Server State Machine
		switch(LINXServer.state)
		{
			case START:
				debugPrintln("Start State");
				LINXServer.begin(6999);
				break;
			
			case LISTENING:
				debugPrintln("Listening State");
				LINXServer.acceptConnection();
				break;					
				
			case CONNECTED:
				debugPrintln("Connected State");
				
				break;	
				
		}	
	}
	
}