all:
	g++ LINX_Pi.cpp LINX_Networking.cpp LINX_Common.cpp device/LINX_Device.cpp -lrt -o LINX
	
test:
	g++ test.cpp LINX_Common.cpp -o test

clean:
	rm -rf *.o
	rm -rf LINX