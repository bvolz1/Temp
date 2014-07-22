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
		int exit();
	
};

#endif //LINX_NETWORKING_H