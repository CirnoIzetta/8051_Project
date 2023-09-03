#include <reg52.h>

#define init 1
#define deinit 0
#define LED P2
#define TIME (65536-46083)
typedef unsigned char uchar;

sbit LED_L = P3^1;
sbit LED_R = P3^0;
uchar digit = 0, count = 0;
void delay(uchar time)
{
	uchar i,j;
	for(i = 0; i < time; ++i)
		for(j = 0; j < time; ++j);
}

void Timer0_Isr(void) interrupt 1
{
	if(++count == 20)
	{
		count = 0;
		if(digit < 100)	digit++;
		else digit = 0;
	}
}

void Timer0_Init(void)		//5ºÁÃë@11.0592MHz
{
	TMOD = 0X01;
	TH0 = TIME / 256;
	TL0 = TIME % 256;
	EA = 1;
	ET0 = 1;
	TR0 = 1;
	
}

void main()
{
	uchar rdigit = 0, ldigit = 0;
	uchar refresh = 0;
	
	//PROTEUS 
	uchar led_seg[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
	
	//CIRCUIT 
	//uchar led_seg[10] = {0x6F,0x0A,0xE3,0xCB,0x8E,0xCD,0xED,0x0B,0xEF,0xCF};
	
	uchar t;
	LED_L = deinit;
	LED_R = deinit;
	Timer0_Init();
	
	while(1)
	{
	
			ldigit = digit % 10;
			rdigit = digit / 10;
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

