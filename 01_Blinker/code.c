#include <reg52.h>
typedef unsigned int uint;
typedef unsigned char uchar;

void delay()
{	
	uint i;
	for(i = 0; i < 20000; ++i);
}


void main()
{
	uchar led;
	led = 0x01;
	while(1)
	{
		P1 = led;
		led = led << 1;
		if(led == 0x00) led = 0x01;
	}
	
}