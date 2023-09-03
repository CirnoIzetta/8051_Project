#include <reg52.h>
//COLUMN FIRST LEFT TO RIGHT REFRESH
#define COL P2			//COLUMN
#define ROW P3			//ROW

typedef unsigned char uchar;
typedef unsigned int uint;
	uchar code refresh_row_bit[]= {
0x00,0x00,0x00,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x7E,0x00,0x00,0x00,0x00,


0x00,0x00,0x00,0x7E,0x60,0x60,0x60,0x7C,0x60,0x60,0x60,0x7E,0x00,0x00,0x00,0x00,


0x00,0x00,0x00,0x78,0x6C,0x66,0x66,0x66,0x66,0x66,0x6C,0x78,0x00,0x00,0x00,0x00};


void delay(uchar time)
{
	uchar i, j;
	for(i = 0; i < time; ++i)
		for(j = 0; j < time; ++j);
}

void main()
{
	uchar i = 0, j = 0;
	uchar offset = 0;
	uchar offset_time = 0;
	//ROW 
	
	
//	uchar refresh_row_bit = 0x01;
	uchar refresh_row_line = 0x00;
	uchar refresh_row_set_bit = 0x01;
													
	//COLUMN REFRESH
	uchar refresh_column_bit   = 0x01;
	uchar refresh_column_index = 0;
	
  
	while(1)
	{
		if(refresh_column_bit == 0x00) refresh_column_bit = 0x01;
		COL = refresh_column_bit;
		ROW = ~refresh_row_bit[i++ + offset];		
		if(i == 8) i = 0,offset_time++;
		refresh_column_bit = refresh_column_bit << 1;
		if(offset_time == 2) offset_time = 0, offset++;
		if(offset + i > sizeof(refresh_row_bit) - 1) offset = 0;
		delay(20);
	}
}
