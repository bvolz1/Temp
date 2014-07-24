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
#include "device/LINX_Device.h"

/****************************************************************************************
**  Constructors
****************************************************************************************/
TCPServer::TCPServer()
{
	state = START;
	timeout.tv_sec = 10;		//Set Socket Time-out To Default Value
	TCPBufIndex = 0;
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

int TCPServer::processPackets(LINXDevice LINXDev)
{
	int received = -1;
	unsigned char packetSize = 0;
	errno = 0;
	
	//Clear SoF
	recBuffer[0] = 0;
	
	//Watch For New Packet
	received = peek(recBuffer, PACKET_BUFFER_SIZE);
	
	//Wait For At Least First Two Bytes Of Packet
	if(received >= 2)
	{
		fprintf(stdout, "SoF = %d \n", recBuffer[0]);
		fprintf(stdout, "Len= %d \n", recBuffer[1]);
		//Check SoF and Packet Size
		if(recBuffer[0] == 0xFF)
		{
			//Valid SoF, Check Packet Size
			packetSize = recBuffer[1];
			if(packetSize < received )
			{
				//Partial Packet, Make Sure Packet Size Will Fit In Buffer, If It Will Loop To Wait For Remainder Of Packet
				if(packetSize > PACKET_BUFFER_SIZE)
				{
					debugPrintln("Packet Size Too Large For Buffer");
					state = EXIT;
					return -1;
				}				
				return 0;
			}			
			else
			{
				//Full Packet In Receive Buffer
				if( received = read(clientsock, recBuffer, packetSize) < 0 )
				{
					//Failed To Read Packet From Buffer
					debugPrintln("Failed To Read Packet From Buffer");
					state = EXIT;
					return -1;				
				}
				else
				{
				
					//Check Checksum
					if(checksumPassed(recBuffer))
					{					
						//Process Packet
						//TODO processCommand(recBuffer, sendBuffer);
						LINXDev.processCommand(recBuffer, sendBuffer);
						
						//Send Response Packet
						unsigned char bytesToSend = sendBuffer[1];
						if( send(clientsock, sendBuffer, bytesToSend, 0) != bytesToSend)
						{
							debugPrintln("Failed To Send Response Packet");
							state = EXIT;
							return -1;
						}
						return 0;
					}
					else
					{
						//Checksum Failed
						debugPrintln("Checksum Failed");
						recv(clientsock, recBuffer, PACKET_BUFFER_SIZE, MSG_DONTWAIT);	
					}
				}
			}
		}
		else
		{
			//Bad SoF, Flush Socket
			debugPrintln("Bad SoF");
			recv(clientsock, recBuffer, PACKET_BUFFER_SIZE, MSG_DONTWAIT);		
		}
	}
}

int TCPServer::stop()
{
	close(serversock);
	close(clientsock);
	
	return 0;
}

int TCPServer::peek(unsigned char * recBuffer, int bufferSize)
{
	int peekReceived = -1;
	errno = 0;
	
	if( (peekReceived = recv(clientsock, recBuffer, bufferSize, MSG_PEEK)) < 0)
	{
		//Time-out Or Error
		if(errno  == EWOULDBLOCK)
		{
			//Time-out Waiting For Data
			debugPrintln("Time-out Waiting For Data");			
		}			
		else
		{
			//Error
			#ifdef DEBUG_ENABLED
				char err[128];
				sprintf(err, "Error %d While Waiting For Data", peekReceived);			
				fprintf(stdout, "%s", (char*) err);
				state = EXIT;
				return peekReceived;
			#endif //DEBUG_ENABLED
		}
	}
	else	 if(peekReceived == 0)
	{		
		//Client Disconnected
		debugPrintln("Client Disconnected");			
		state = EXIT;		
	}
	else
	{
		//Data Received
		return peekReceived;		
	}
}


	