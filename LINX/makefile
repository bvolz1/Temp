all: release debug
	
release:
	g++ LINX_Daemon.cpp LINX_Networking.cpp LINX_Common.cpp device/LINX_Device.cpp device/Raspberry_Pi/LINX_Raspberry_Pi.cpp device/Raspberry_Pi/LINX_Raspberry_Pi_B.cpp -lrt -o LINX_Release.out
	
debug:
	g++ LINX_Daemon.cpp LINX_Networking.cpp LINX_Common.cpp device/LINX_Device.cpp device/Raspberry_Pi/LINX_Raspberry_Pi.cpp device/Raspberry_Pi/LINX_Raspberry_Pi_B.cpp -lrt -DDEBUG_ENABLED=1 -o LINX_Debug.out
	
test:
	g++ test.cpp LINX_Common.cpp -o test

clean:
	rm -rf *.o
	rm -rf *.out