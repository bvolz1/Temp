
MAKE_RASPBERRYPI = $(MAKE) -f MakeRaspberryPi
RASPBERRYPI_ALL = raspberrypia raspberrypib raspberrypibplus

MAKE_ARDUINO = $(MAKE) -f MakeArduino

arduino: arduinouno arduinomega2560

raspberrypi: raspberrypia raspberrypib raspberrypibplus

raspberrypia:
	$(MAKE_RASPBERRYPI) raspberrypia SERIAL_LISTENER=1
	$(MAKE_RASPBERRYPI) raspberrypia TCP_LISTENER=1

raspberrypib:
	$(MAKE_RASPBERRYPI) raspberrypib SERIAL_LISTENER=1
	$(MAKE_RASPBERRYPI) raspberrypib TCP_LISTENER=1

raspberrypibplus:	
	$(MAKE_RASPBERRYPI) raspberrypibplus SERIAL_LISTENER=1
	$(MAKE_RASPBERRYPI) raspberrypibplus TCP_LISTENER=1
	
	
arduinouno:
	$(MAKE_ARDUINO) BOARD_TAG=uno SERIAL_LISTENER=1
	
arduinomega2560:
	#$(MAKE_ARDUINO) BOARD_TAG=mega2560 SERIAL_LISTENER=1