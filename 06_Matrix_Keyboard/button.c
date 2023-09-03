#include <reg52.h>
//P2.0-P2.3 ROW      P2.4-2.7 COL				COL ROW
#define PORT P2
#define LED P0
#define INIT 1
#define DEINIT 0
//DEFAULT ALL UP
#define COL_DOWN_ROW_UP  0x0F
#define COL_UP_ROW_DOWN 0xF0
typedef unsigned int uint;
typedef unsigned char uchar;
sbit LED_L = P1^0;
sbit LED_R = P1^1;
uchar i = 0,j = 0;

//PROTEUS
uchar led_seg [4][4] = {0x3f,0x06,0x5b,0x4f,
												0x66,0x6d,0x7d,0x07,
												0x7f,0x6f,0x77,0x7c,
												0x39,0x5e,0x79,0x71};
 



//CIRCUIT
//uchar led_seg [4][4] = {0x6F,0x0A,0xE3,0xCB,
//											0x8E,0xCD,0xED,0x0B,
//										    0xEF,0xCF,0xaf ,0xec,
//												0x65,0xea,0xe5,0xa5};

void delay(uchar time);
uchar button_read();
uchar keyboard_read();
void display(uchar ch);											
void main()
{ 
	uchar ch;
	while(1)
	{
		ch = keyboard_read();
		display(ch);
	}
}



uchar button_read()
{
	uchar k = 0;
	uchar row;
	PORT = 0xf0;
	
	if((PORT & 0xf0) != 0xf0)	//clear low 4
	{
	//	delay(1);
		if((PORT & 0xf0) != 0xf0)
		{
			row = 0xfe;
			while((row & 0x10) != 0x00)
			{
				PORT = row;
				if((PORT & 0xf0) != 0xf0)
				{
					k = PORT;
					k = ~k;
					return k;
				}
				else row = (row << 1) | 0x01;
			}
		}
		return k;
	}	
}	
	


uchar keyboard_read()
{
	
	uchar key;
	key = button_read();
	if(key == 0) return 0x00; 
	
	//i get
	
	if(key & 0x01)			i = 0;
	else if(key & 0x02) i = 1;
	else if(key & 0x04) i = 2;
	else if(key & 0x08) i = 3;
	
	if(key & 0x10)			j = 0;
	else if(key & 0x20) j = 1;
	else if(key & 0x40) j = 2;
	else if(key & 0x80) j = 3;
	
	return led_seg[i][j];	
}

void display(uchar loc)
{
		uchar t,refresh, seg_data;
		seg_data = loc;
		for(t = 0; t < 20; ++t)
		for(refresh = 0; refresh < 2; ++refresh)
		{
			if(refresh == 0)
			{
					LED_L = 1;
					LED = ~seg_data;
			 		delay(2);
					LED_L = 0;
			}
			else if(refresh == 1)
			{
					LED_R = 1;
					LED = ~seg_data;
					delay(2);
					LED_R = 0;
			}
		}
}

void delay(uchar t)
{
	uchar i,j;
	for(i = 0; i < 100; ++i)
		for(j = 0; j < t; ++j);
}