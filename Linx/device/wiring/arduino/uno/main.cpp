#include <Arduino.h>

int main()
{
	
	pinMode(13, OUTPUT);

	digitalWrite(13, HIGH);
	delay(1);
	digitalWrite(13, LOW);
	
	return  0;

}