#include <stdio.h>

#include "LinxCommon.h"
#include "device/LinxDevice.h"
#include "device/raspberrypi/LinxRaspberryPi-B.h"

LinxRaspberryPiB LinxDev;	

int main(int argc, char *argv[])
{
	printf("Linx Main...\n\n");
	
	unsigned char pins[1] = {18};
	unsigned char values[1] = {LOW};

	for(int i=0; i<200000; i++)
	{
		values[0] = LOW;
		LinxDev.DigitalWrite(1, pins, values);
		values[0] = HIGH;
		LinxDev.DigitalWrite(1, pins, values);
	}
	
	return 0;
}