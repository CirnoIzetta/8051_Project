#include <reg52.h>
//SEG A-G-DP     BIT 1 2
#define INT_BUTTON P3
#define SEG P0
#define BIT P2
#define T (8192-0000)
typedef unsigned int uint;
typedef unsigned char uchar;
uchar count = 0;
uchar l = 0, r = 0;
//0 LEFT     1RIGHT
uchar bit_led[2] = {0x3f,0x3f};
uchar segment[] = {0x01,0x02};
uchar led_index = 0;
uchar flag = 0;
//PROTEUS
uchar digit[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

//CIRCUIT 
//uchar digit[] = {0x6F,0x0A,0xE3,0xCB,0x8E,0xCD,0xED,0x0B,0xEF,0xCF};

uchar button_flag = 0;
void delay(uchar t)
{
	uchar i, j;
	for(i = 0; i < t; ++i)
		for(j = 0; j < t; ++j);
}


void init()
{
	//INIT LED SEG REFRESH TIMER AND INTERRUPT
	TMOD = 0X00;
	TL0 = T % 32;
	TH0 = T / 32;
	TR0 = 1;
	
	//INIT EXTENAL PIN 
	
	//INT0 EN
	EX0 = 1;
	//INT0 1 DOWN PULSE AS TRIGGER
	IT0 = 1;
	
	
	//INT1 EN
	EX1 = 1;
	//INT1 1 DOWN PULSE AS TRIGGER
	IT1 = 1;
	
	EA  = 1;
	ET0 = 1;	
}



void main()
{
	init();
	while(1)
	{
		if((flag == 1 || flag == 2)& INT_BUTTON == 0xFF)
		{
			delay(10);
			if(INT_BUTTON == 0xFF) flag = 0;
		}
	}
}


//BUTTON1 CONNECT TO P3^2
void button1_pressed(void) interrupt 0
{
	delay(10);
	if(INT_BUTTON == 0xFB && flag == 0) 
	{
		delay(10);
		count++;
		bit_led[0] = digit[count/10];
		bit_led[1] = digit[count%10];
		flag = 1;
	}
}

//BUTTON2 CONNECT TO P3^3
void button2_pressed(void) interrupt 2// 
{
	delay(10);
	if(INT_BUTTON == 0xF7 && flag == 0)
	{
		delay(10);
		if(count > 0) 
		{
			count--;
			bit_led[0] = digit[count/10];
			bit_led[1] = digit[count%10];	
		}
		flag = 2;
	}
	
}

//LED SEG REFRESH
void ledseg_refresh(void) interrupt 1
{
	BIT = segment[led_index];
	SEG = ~bit_led[led_index];
	//BIT = segment[led_index];
	led_index++;
	if(led_index == 2) led_index = 0;
	TL0 = T % 32;
	TH0 = T / 32;
}
