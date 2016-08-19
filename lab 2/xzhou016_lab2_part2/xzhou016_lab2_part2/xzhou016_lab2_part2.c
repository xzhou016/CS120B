/*	xzhou016_lab2_part2.c - $date$
 *	Name & E-mail:  - Xiao Zhou, xzhou016@ucr.edu 
 *	CS Login: xzhou016
 *	Partner(s) Name & E-mail:  - Jia Jun Yu, jyu052@ucr.edu
 *	Lab Section: 
 *	Assignment: Lab #2  Exercise #1 
 *	Exercise Description: dunno
 *	
 *	
 *	I acknowledge all content contained herein, excluding template or example 
 *	code, is my own original work.
 */ 


#include <avr/io.h>

// Bit-access function
unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;

	DDRC = 0xFF; PORTC = 0x00;
	

	
	
	while(1)
	{
		if ((PINA > 0x0C) && (PINA <= 0x0F))
		{
			PORTC = SetBit(PORTC, 0, 1);	
		}else
		{
			PORTC = SetBit(PORTC, 0, 0);
		}
		
		if ((PINA > 0x09) && (PINA <= 0x0F))
		{
			PORTC = SetBit(PORTC, 1, 1);
							
		}else
		{
			PORTC = SetBit(PORTC, 1, 0);
		}
		
		if ((PINA > 0x06) && (PINA <= 0x0F))
		{
			PORTC = SetBit(PORTC, 2, 1);
						
		}else
		{
			PORTC = SetBit(PORTC, 2, 0);
		}
		
		if ((PINA > 0x04) && (PINA <= 0x0F))
		{
			PORTC = SetBit(PORTC, 3, 1);
					
		}else
		{
			PORTC = SetBit(PORTC, 3, 0);
		}
		
		if ((PINA > 0x02) && (PINA <= 0x0F))
		{
			PORTC = SetBit(PORTC, 4, 1);
		}else
		{
			PORTC = SetBit(PORTC, 4, 0);
		}
		
		if ((PINA > 0x00) && (PINA <= 0x0F))
		{
			PORTC = SetBit(PORTC, 5, 1);
		}else
		{
			PORTC = SetBit(PORTC, 5, 0);
		}
		
		if ((PINA > 0x00) && (PINA <= 0x04))
		{
			PORTC = SetBit(PORTC, 6, 1);
		}
		else
		{
			PORTC = SetBit(PORTC, 6, 0);	
		}
	}
}