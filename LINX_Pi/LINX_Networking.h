#ifndef LINX_NETWORKING_H
#define LINX_NETWORKING_H

//Variables
enum TCPServerState {START, LISTENING, CONNECTED, CLOSE, EXIT};

class TCPServer
{
	public:	
		/****************************************************************************************
		**  Variables
		****************************************************************************************/		
		TCPServerState state;
		
		unsigned char recBuffer[TCP_BUFF_SIZE];
		
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
		int checkForPacket();
		int stop();
	
};

#endif //LINX_NETWORKING_H