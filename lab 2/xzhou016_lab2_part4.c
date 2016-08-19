/*	xzhou016_lab2_part4.c - $date$
 *	Name & E-mail:  - Xiao Zhou, xzhou016@ucr.edu 
 *	CS Login: xzhou016
 *	Partner(s) Name & E-mail:  - Jia Jun Yu, jyu052@ucr.edu
 *	Lab Section: 
 *	Assignment: Lab #2  Exercise #4
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
	DDRB = 0x0F; PORTB = 0x00;
	DDRC = 0x0F; PORTC = 0x00;
    while(1)
    {
		unsigned char tempB = 0x00, tempC = 0x00;
		tempB = ((PINA & 0xF0) >> 4);
		tempC = PINA & 0x0F;
		PORTB = tempB;
		PORTC = tempC;
    }
}