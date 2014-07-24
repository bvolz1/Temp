#ifndef LINX_DEVICE_H
#define LINX_DEVICE_H


class LINXDevice
{
	public:	
		/****************************************************************************************
		**  Variables
		****************************************************************************************/		
		unsigned char familyCode;
		unsigned char deviceCode;
		
		/****************************************************************************************
		**  Constructors
		****************************************************************************************/
		LINXDevice();
			
		/****************************************************************************************
		**  Functions
		****************************************************************************************/
		void processCommand(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer);
		void statusResponse(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer, unsigned char linxStatus);
		void getDeviceID(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer);
		
		
	private:
		/****************************************************************************************
		**  Variables
		****************************************************************************************/		
				
		
		/****************************************************************************************
		**  Functions
		****************************************************************************************/
		
		
};


#endif //LINX_DEVICE_H
