all: release debug
	
release:
	g++ LinxTcpDaemon.cpp comms/LinxTcp.cpp common/LinxCommon.cpp device/LinxDevice.cpp device/raspberrypi/LinxRaspberryPi.cpp device/raspberrypi/LinxRaspberryPi-B.cpp -lrt -o LinxRelease.out
	
debug:
	g++ LinxTcpDaemon.cpp listener/LinxTcpListener.cpp listener/linux/LinxTcpListenerLinux.cpp common/LinxCommon.cpp device/LinxDevice.cpp device/raspberrypi/LinxRaspberryPi.cpp device/raspberrypi/LinxRaspberryPi-B.cpp -lrt -DDEBUG_ENABLED=1 -o LinxDebug.out
	
main:
	g++ main.cpp device/LinxDevice.cpp device/raspberrypi/LinxRaspberryPi.cpp device/raspberrypi/LinxRaspberryPi-B.cpp -lrt  -DDEBUG_ENABLED=1 -o main.out

clean:
	rm -rf *.o
	rm -rf *.out
