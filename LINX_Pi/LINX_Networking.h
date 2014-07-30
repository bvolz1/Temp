#ifndef LINX_NETWORKING_H

#define LINX_NETWORKING_H
#include "device/LINX_Device.h"

#ifndef PACKET_BUFFER_SIZE
	#define PACKET_BUFFER_SIZE 64
#endif

#ifndef MAX_PENDING_CONS
	#define MAX_PENDING_CONS 2
#endif

//Variables
enum TCPServerState {START, LISTENING, CONNECTED, RESTART, EXIT};

class TCPServer
{
	public:	
		/****************************************************************************************
		**  Variables
		****************************************************************************************/		
		TCPServerState state;
		
		unsigned char recBuffer[PACKET_BUFFER_SIZE];
		unsigned char sendBuffer[PACKET_BUFFER_SIZE];
		
		unsigned long TCPUpdateTime;
		struct timeval timeout;
		
		int serversock;
		int clientsock;		
	
		struct sockaddr_in echoserver;
		struct sockaddr_in echoclient;
	
		/****************************************************************************************
		**  Constructors
		****************************************************************************************/
		TCPServer();		//Default Constructor
	
	
		/****************************************************************************************
		**  Functions
		****************************************************************************************/
		int begin(unsigned int serverPort);
		int acceptConnection();
		int processPackets(LINXDevice LINXDev);
		int stop();
	
	private:
		/****************************************************************************************
		**  Variables
		****************************************************************************************/		
		int TCPBufIndex;
		
		
		/****************************************************************************************
		**  Functions
		****************************************************************************************/
		int peek(unsigned char * recBuffer, int bufferSize);
		
};

#endif //LINX_NETWORKING_H