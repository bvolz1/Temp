all: release debug main
	
release:
	g++ LinxTcpDaemon.cpp  listener/LinxTcpListener.cpp listener/linux/LinxTcpListenerLinux.cpp   device/raspberrypi/LinxRaspberryPi-B.cpp -lrt -o LinxRelease.out
	
debug:
	g++ LinxTcpDaemon.cpp listener/LinxListener.cpp listener/LinxTcpListener.cpp listener/linux/LinxTcpListenerLinux.cpp device/LinxDevice.cpp device/raspberrypi/LinxRaspberryPi.cpp device/raspberrypi/LinxRaspberryPi-B.cpp -lrt -DDEBUG_ENABLED=1 -o LinxDebug.out
	
serial: 
	g++ LinxSerialDaemon.cpp listener/LinxListener.cpp listener/LinxSerialListener.cpp device/LinxDevice.cpp device/raspberrypi/LinxRaspberryPi.cpp device/raspberrypi/LinxRaspberryPi-B.cpp -lrt -DLINXDEVICE=LinxRaspberryPiB -DDEBUG_ENABLED=1 -o serialdebug.out

uno:	
	cd device/wiring/arduino/uno && make	

clean:
	rm -rf *.o
	rm -rf *.out
	rm -rf bin/*
