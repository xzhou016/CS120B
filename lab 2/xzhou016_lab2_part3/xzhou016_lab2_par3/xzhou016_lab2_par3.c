/*	xzhou016_lab2_part3.c - $date$
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
	DDRA = 0x00; PORTA = 0x00;

	DDRC = 0xFF; PORTC = 0x00;
	

	
	
	while(1)
	{
		if (((PINA & 0x0F) > 0x0C) && ((PINA & 0x0F) <= 0x0F))
		{
			PORTC = SetBit(PINC, 0, 1);	
		}else
		{
			PORTC = SetBit(PINC, 0, 0);
		}
		
		if (((PINA & 0x0F) > 0x09) && ((PINA & 0x0F) <= 0x0F))
		{
			PORTC = SetBit(PINC, 1, 1);
							
		}else
		{
			PORTC = SetBit(PINC, 1, 0);
		}
		
		if (((PINA & 0x0F) > 0x06) && ((PINA & 0x0F) <= 0x0F))
		{
			PORTC = SetBit(PINC, 2, 1);
						
		}else
		{
			PORTC = SetBit(PORTC, 2, 0);
		}
		
		if (((PINA & 0x0F) > 0x04) && ((PINA & 0x0F) <= 0x0F))
		{
			PORTC = SetBit(PINC, 3, 1);
					
		}else
		{
			PORTC = SetBit(PINC, 3, 0);
		}
		
		if (((PINA & 0x0F) > 0x02) && ((PINA & 0x0F) <= 0x0F))
		{
			PORTC = SetBit(PINC, 4, 1);
		}else
		{
			PORTC = SetBit(PINC, 4, 0);
		}
		
		if (((PINA & 0x0F) > 0x00) && ((PINA & 0x0F) <= 0x0F))
		{
			PORTC = SetBit(PINC, 5, 1);
		}else
		{
			PORTC = SetBit(PINC, 5, 0);
		}
		
		if (((PINA & 0x0F) > 0x00) && ((PINA & 0x0F) <= 0x04))
		{
			PORTC = SetBit(PINC, 6, 1);
		}
		else
		{
			PORTC = SetBit(PINC, 6, 0);	
		}
		
		//driver safety check A.K.A part 3
		if ((GetBit(PINA, 4) == 0x01) && (GetBit(PINA, 5) == 0x01) && (GetBit(PINA, 6) == 0x00))
		{
			PORTC = SetBit(PINC, 7, 1);
		}else
		{
			PORTC = SetBit(PINC, 7, 0);
		}
	}
}