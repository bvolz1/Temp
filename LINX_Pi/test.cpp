#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#ifndef NUMBER
#define NUMBER 10
#endif

int main()
{
	fprintf(stdout, "hello   %d \n", NUMBER);
}