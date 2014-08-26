all: release debug main
	
release:
	g++ LinxTcpDaemon.cpp listener/LinxListener.cpp listener/LinxTcpListener.cpp listener/linux/LinxTcpListenerLinux.cpp LinxCommon.cpp device/LinxDevice.cpp device/raspberrypi/LinxRaspberryPi.cpp device/raspberrypi/LinxRaspberryPi-B.cpp -lrt -o LinxRelease.out
	
debug:
	g++ LinxTcpDaemon.cpp listener/LinxListener.cpp listener/LinxTcpListener.cpp listener/linux/LinxTcpListenerLinux.cpp LinxCommon.cpp device/LinxDevice.cpp device/raspberrypi/LinxRaspberryPi.cpp device/raspberrypi/LinxRaspberryPi-B.cpp -lrt -DDEBUG_ENABLED=1 -o LinxDebug.out
	
serial: 
	g++ LinxSerialDaemon.cpp listener/LinxListener.cpp listener/LinxSerialListener.cpp LinxCommon.cpp device/LinxDevice.cpp device/raspberrypi/LinxRaspberryPi.cpp device/raspberrypi/LinxRaspberryPi-B.cpp -lrt -DDEBUG_ENABLED=1 -o serialdebug.out
	
main:
	g++ main.cpp LinxCommon.cpp device/LinxDevice.cpp device/raspberrypi/LinxRaspberryPi.cpp device/raspberrypi/LinxRaspberryPi-B.cpp -lrt  -o main.out
	
maindebug:
	g++ main.cpp LinxCommon.cpp device/LinxDevice.cpp device/raspberrypi/LinxRaspberryPi.cpp device/raspberrypi/LinxRaspberryPi-B.cpp -lrt  -DDEBUG_ENABLED=1 -o maindebug.out

clean:
	rm -rf *.o
	rm -rf *.out
