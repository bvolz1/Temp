/****************************************************************************************
**  Includes
****************************************************************************************/
#include "LinxListener.h"
#include "LinxTcpListener.h"

/****************************************************************************************
**  Constructors
****************************************************************************************/
LinxTcpListener::LinxTcpListener()
{
	State = START;
	Interface = TCP;
}

/****************************************************************************************
**  Functions
****************************************************************************************/
