#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#include "LINX_Config.h"
#include "LINX_Common.h"
#include "LINX_Networking.h"

/****************************************************************************************
**  Constructors
****************************************************************************************/
TCPServer::TCPServer()
{
	state = START;
	timeout.tv_sec = 10;		//Set Socket Time-out To Default Value
}

/****************************************************************************************
**  Functions
****************************************************************************************/

int TCPServer::begin(unsigned int serverPort)
{
	debugPrintln("Starting LINX TCP Server!");
	
	//Create the TCP socket
	if((serversock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) 
	{
		debugPrintln("Failed To Create Socket");
		state = EXIT;
		return -1;
	}
	else
	{
		debugPrintln("Successfully Created Socket");
	}
	
	
	
	//Construct the server sockaddr_in structure
	memset(&echoserver, 0, sizeof(echoserver));			//Clear Struct
	echoserver.sin_family = AF_INET;							//Internet/IP
	echoserver.sin_addr.s_addr = htonl(INADDR_ANY); 	//Incoming Addr
	echoserver.sin_port = htons(serverPort);			//Server Port
	
	//Bind the server socket
	if( bind(serversock, (struct sockaddr *) &echoserver, sizeof(echoserver)) < 0)
	{
		debugPrintln("Failed To Bind Sever Socket");
		state = EXIT;
		return -1;
	}
	else
	{
		debugPrintln("Successfully Bound Sever Socket");
	}
	
	//Listen on the server socket
	if(listen(serversock, MAX_PENDING_CONS) < 0)
	{
		debugPrintln("Failed To Start Listening On Sever Socket");
		state = EXIT;
		return -1;
	}
	else
	{
		debugPrintln("Successfully Started Listening On Sever Socket");
		state = LISTENING;
	}
	
	return 0;
}

int TCPServer::acceptConnection()
{
	debugPrintln("Waiting For Client Connection");
	
	unsigned int clientlen = sizeof(echoclient);
	
	if( (clientsock = accept(serversock, (struct sockaddr *) &echoclient, &clientlen)) < 0)
	{
		("Failed To Accept Client Connection");
		state = EXIT;
		return -1;
	}
	else
	{		
		if ( setsockopt (clientsock, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
		{
			debugPrintln("Failed To Set Socket Receive Time-out");
			return -1;
		}
		else
		{
			
			TCPUpdateTime = getSeconds();
			state = CONNECTED;
			debugPrint(inet_ntoa(echoclient.sin_addr));
			debugPrintln(" Successfully Connected");
		}		
	}
	return 0;	
}

int TCPServer::checkForPacket()
{
	int received = -1;
	
	if( (received = recv(clientsock, recBuffer, TCP_BUFF_SIZE, 0)) <= 0)
	{
		//Time-out Or Error
		if(errno  == EWOULDBLOCK)
		{
			//Time-out Waiting For Data
			debugPrintln("Time-out Waiting For Data");			
		}
		else if(received == 0)
		{
			//Client Disconnected
			state = EXIT;
		}		
		else
		{
			//Error
			char err[128];
			sprintf(err, "Error %d While Waiting For Data", received);			
			fprintf(stdout, "%s", (char*) err);
			state = EXIT;
			return -1;
		}		
	}	
	else
	{
		//Data Received
		char out[256];
		sprintf(out, "Received %d Bytes : %s \n", received, recBuffer);		
		fprintf(stdout, "%s", (char*) out);		
	}

}

int TCPServer::stop()
{
	close(serversock);
	close(clientsock);
	
	return 0;
}


	