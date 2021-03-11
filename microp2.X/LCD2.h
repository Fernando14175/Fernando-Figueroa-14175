#ifndef __LCD2_H
#define	__LCD2_H

#include <xc.h> // include processor files - each processor file is guarded.  
void LCD_data(char y);
void LCD_cmd(char y);

 void delay(unsigned int x)
{
	while(x--);
}
 
 void LCD_init()
{
	TRISB = 0x00;
	PORTB = 0x00;
	TRISD2 = 0;
	TRISD3 = 0;
	delay(200);
	LCD_cmd(0x0c);
	LCD_cmd(0x06);
	LCD_cmd(0x38);
	LCD_cmd(0x80);
}
void LCD_disp(unsigned char y)
{
	int temp = y/10;
	LCD_data(temp);
	delay(100);
	temp = y%10;
	LCD_data(temp);
	delay(100);
}

void LCD_cmd(char y)
{
	RD2 = 0;
	RD3 = 1;
	PORTB = y;
	delay(100);
    RD3 = 0;
    delay(100);
}

void LCD_data(char y)
{
	RD2 = 1;
	RD3 = 1;
	PORTB = y + 48;
	delay(100);
	RD3 = 0;
	delay(200);
}

#endif	/* SPI_H */
