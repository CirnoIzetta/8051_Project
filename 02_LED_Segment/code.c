#include <reg52.h>

#define init 1
#define deinit 0
#define LED P0
//#define LED P0
typedef unsigned char uchar;


//sbit LED_L = P3^1;
//sbit LED_R = P3^0;
sbit LED_L = P2^1;
sbit LED_R = P2^0;
void delay(uchar time)
{
	uchar i,j;
	for(i = 0; i < time; ++i)
		for(j = 0; j < time; ++j);
}


void main()
{
	char digit = 99;
	uchar rdigit = 0, ldigit = 0;
	uchar refresh = 0;
	
	//PROTEUS 
	//uchar led_seg[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
	
	//CIRCUIT 
	uchar led_seg[10] = {0x6F,0x0A,0xE3,0xCB,0x8E,0xCD,0xED,0x0B,0xEF,0xCF};
	
	uchar t;
	LED_L = deinit;
	LED_R = deinit;
	while(1)
	{
		digit  = 99;
		for(;digit >= 0; digit--)
		{
			
			ldigit = digit % 10;
			rdigit = digit / 10;
			P1 = digit;
			for(t = 0; t < 20; ++t)
			for(refresh = 0; refresh < 2; ++refresh)
			{
				if(refresh == 0)
				{
						LED_L = init;
						LED = ~(led_seg[ldigit]);
			   		delay(20);
						LED_L = deinit;
				}
				else if(refresh == 1)
				{
						LED_R = init;
						LED = ~(led_seg[rdigit]);
						delay(20);
						LED_R = deinit;
				}
			}
			
		}
	}
}
