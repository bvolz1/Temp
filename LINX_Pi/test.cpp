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


class base
{
	public:	
		
		unsigned char* pointer;
		//Constructors
		base()
		{
			fprintf(stdout, "New Base\n");			
			fprintf(stdout, "Pointer at %d \n", *pointer);
			
			//fprintf(stdout, "Pointer2 at %d \n", *pointer2);
		}
};

class child : public base
{
	public:	
	unsigned char chars[3];
	
	child()
	{
		unsigned char m_chars[3] = {'a', 'b', 'c'};
		memcpy(chars, m_chars, 3);			
		pointer = chars;
	}
};

class otherClass
{
	public:	
		
		void printPointer(base lBase)
		{
			fprintf(stdout, "Other Class Pointer at %d \n", *lBase.pointer);
			for(int i=0; i<3; i++)
			{
				fprintf(stdout, "%c ", lBase.pointer[i]);
			}
			//fprintf(stdout, "Other Class Pointer2 at %d \n", *lBase.pointer2);
		}

};


int main()
{
	child myChild;
    otherClass myOther;
	
	fprintf(stdout, "Main -> Pointer@ %d\n", *myChild.pointer);
	
	for(int i=0; i<3; i++)
	{
		fprintf(stdout, "%c ", myChild.pointer[i]);
	}
	//fprintf(stdout, "Main -> Pointer2@ %d\n", *myBase.pointer2);
	
	myOther.printPointer(myChild);
}

