#ifndef LINX_TCP_LISTENER_LINUX_H
#define LINX_TCP_LISTENER_LINUX_H

/****************************************************************************************
**  Functions
****************************************************************************************/
#ifndef PACKET_BUFFER_SIZE
	#define PACKET_BUFFER_SIZE 64
#endif

#ifndef MAX_PENDING_CONS
	#define MAX_PENDING_CONS 2
#endif

/****************************************************************************************
**  Includes
****************************************************************************************/
#include "../LinxTcpListener.h"
#include "../../device/LinxDevice.h"

class LinxTcpListenerLinux : public LinxTcpListener
{
	public:	
		/****************************************************************************************
		**  Variables
		****************************************************************************************/		
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
		LinxTcpListenerLinux();		//Default Constructor
	
	
		/****************************************************************************************
		**  Functions
		****************************************************************************************/
		int Start(unsigned int serverPort);
		int Accept();
		int Connected(LinxDevice &linxDev);
		int Exit();
	
	private:
		/****************************************************************************************
		**  Variables
		****************************************************************************************/		
		int TCPBufIndex;		
		
		/****************************************************************************************
		**  Functions
		****************************************************************************************/
		int Peek(unsigned char * recBuffer, int bufferSize);
		
};

#endif //LINX_TCP_LISTENER_LINUX_H