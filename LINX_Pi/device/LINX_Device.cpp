#include "../LINX_Config.h"
#include "../LINX_Common.h"
#include "LINX_Device.h"


/****************************************************************************************
**  Constructors
****************************************************************************************/
LINXDevice::LINXDevice()
{
	unsigned char familyCode = 0xFE;
	unsigned char deviceCode = 0x00;		
}


/****************************************************************************************
**  Functions
****************************************************************************************/
void LINXDevice::statusResponse(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer, unsigned char linxStatus)
{
	responsePacketBuffer[0] = 0xFF;															//SoF
	responsePacketBuffer[1] = 0x06;															//PACKET SIZE
	responsePacketBuffer[2] = commandPacketBuffer[2];								//PACKET NUM (MSB)
	responsePacketBuffer[3] = commandPacketBuffer[3];								//PACKET NUM (LSB)
	responsePacketBuffer[4] = linxStatus;														//STATUS
	responsePacketBuffer[5] = computeChecksum(responsePacketBuffer);		//Checksum  
}

void LINXDevice::getDeviceID(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer)
{
	responsePacketBuffer[0] = 0xFF;															//SoF
	responsePacketBuffer[1] = 0x08;															//PACKET SIZE
	responsePacketBuffer[2] = commandPacketBuffer[2];								//PACKET NUM (MSB)
	responsePacketBuffer[3] = commandPacketBuffer[3];								//PACKET NUM (LSB)
	responsePacketBuffer[4] = 0x00;															//STATUS  
	responsePacketBuffer[5] = familyCode; 													//Family Code
	responsePacketBuffer[6] = deviceCode; 													//Device Code
	responsePacketBuffer[7] = computeChecksum(responsePacketBuffer);		//Checksum
}

void LINXDevice::processCommand(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer)
{
	debugPrintln("LINXDev Processing Command ");
	
	for(int i=0; i< PACKET_BUFFER_SIZE; i++)
	{
		responsePacketBuffer[i] = commandPacketBuffer[i];
	}
}