all: release debug
	
release:
	g++ LinxTcpDaemon.cpp comms/LinxTcp.cpp common/LinxCommon.cpp device/LinxDevice.cpp device/raspberrypi/LinxRaspberryPi.cpp device/raspberrypi/LinxRaspberryPi-B.cpp -lrt -o LinxRelease.out
	
debug:
	g++ LinxTcpDaemon.cpp comms/LinxTcp.cpp common/LinxCommon.cpp device/LinxDevice.cpp device/raspberrypi/LinxRaspberryPi.cpp device/raspberrypi/LinxRaspberryPi-B.cpp -lrt -DDEBUG_ENABLED=1 -o LinxDebug.out
	
ArduinoSerial:
	g++ LinxSerial.cpp LinxSerialDaemon.cpp LinxCommon.cpp device/LinxDevice.cpp device/Arduino/ArduinoSerialDaemon.cpp -lrt  -DDEBUG_ENABLED=1 -o LinxSerial.out

clean:
	rm -rf *.o
	rm -rf *.out
