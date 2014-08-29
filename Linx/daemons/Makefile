
MAKE_RASPBERRYPI = $(MAKE) -f MakeRaspberryPi
RASPBERRYPI_ALL = raspberrypia raspberrypib raspberrypibplus

MAKE_ARDUINO = $(MAKE) -f MakeArduino

#ALL
all: arduino raspberrypi
clean: raspberrypiclean arduinoclean

#Arduino
arduino: arduinouno

arduinoclean: 
	$(MAKE_ARDUINO) BOARD_TAG=uno clean	
	rm -r ../bin/device ../bin/listener
	
arduinouno:
	$(MAKE_ARDUINO) BOARD_TAG=uno SERIAL_LISTENER=1
	

#Raspberry Pi
raspberrypi: raspberrypia raspberrypib raspberrypibplus

raspberrypiclean: 
	$(MAKE_RASPBERRYPI) clean

raspberrypia:
	$(MAKE_RASPBERRYPI) raspberrypia SERIAL_LISTENER=1
	$(MAKE_RASPBERRYPI) raspberrypia TCP_LISTENER=1

raspberrypib:
	$(MAKE_RASPBERRYPI) raspberrypib SERIAL_LISTENER=1
	$(MAKE_RASPBERRYPI) raspberrypib TCP_LISTENER=1

raspberrypibplus:	
	$(MAKE_RASPBERRYPI) raspberrypibplus SERIAL_LISTENER=1
	$(MAKE_RASPBERRYPI) raspberrypibplus TCP_LISTENER=1

