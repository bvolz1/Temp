all: release debug main
	
release:
	g++ LinxTcpDaemon.cpp listener/LinxListenerCommon.cpp listener/LinxTcpListener.cpp listener/linux/LinxTcpListenerLinux.cpp LinxCommon.cpp device/LinxDevice.cpp device/raspberrypi/LinxRaspberryPi.cpp device/raspberrypi/LinxRaspberryPi-B.cpp -lrt -o LinxRelease.out
	
debug:
	g++ LinxTcpDaemon.cpp listener/LinxListenerCommon.cpp listener/LinxTcpListener.cpp listener/linux/LinxTcpListenerLinux.cpp LinxCommon.cpp device/LinxDevice.cpp device/raspberrypi/LinxRaspberryPi.cpp device/raspberrypi/LinxRaspberryPi-B.cpp -lrt -DDEBUG_ENABLED=1 -o LinxDebug.out
	
main:
	g++ main.cpp device/LinxDevice.cpp device/raspberrypi/LinxRaspberryPi.cpp device/raspberrypi/LinxRaspberryPi-B.cpp -lrt  -DDEBUG_ENABLED=1 -o main.out

clean:
	rm -rf *.o
	rm -rf *.out
