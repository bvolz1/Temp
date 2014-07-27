all:
	g++ LINX_Pi.cpp LINX_Networking.cpp LINX_Common.cpp device/LINX_Device.cpp device/Raspberry_Pi/LINX_Raspberry_Pi.cpp device/Raspberry_Pi/LINX_Raspberry_Pi_B.cpp -lrt -DDEVICE_FAMILY=0x04 -DDEVICE_ID=0x01 -o LINX
	
test:
	g++ test.cpp LINX_Common.cpp -o test

clean:
	rm -rf *.o
	rm -rf LINX