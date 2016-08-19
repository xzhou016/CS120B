/*	xzhou016_lab2_part1.c - $date$
 *	Name & E-mail:  - Xiao Zhou, xzhou016@ucr.edu 
 *	CS Login: xzhou016
 *	Partner(s) Name & E-mail:  - Jia Jun Yu, jyu052@ucr.edu
 *	Lab Section: 
 *	Assignment: Lab #2  Exercise #1 
 *	Exercise Description: 
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
	DDRB = 0x00; PORTB = 0xFF;

	DDRC = 0xFF; PORTC = 0x00;
	

	
	
	while(1)
	{
		unsigned char tempBit = 0x00;
		for (unsigned char i = 0x00 ; i < 0x08 ; i++)
		{
			tempBit = tempBit +  GetBit(PINA , i) + GetBit(PINB, i);
		}
		
		PORTC = tempBit;
	}
}