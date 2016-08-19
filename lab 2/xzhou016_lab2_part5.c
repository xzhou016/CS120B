/*	xzhou016_lab2_part5.c - 7/26/2016 3:38:16 PM
 *	Name & E-mail:  - Xiao Zhou, xzhou016@ucr.edu 
 *	CS Login: xzhou016
 *	Partner(s) Name & E-mail:  - Jia Jun Yu, jyu052@ucr.edu
 *	Lab Section: 
 *	Assignment: Lab #2  Exercise #5
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
	DDRB = 0x06; PORTB = 0x00;
	DDRD = 0x00; PORTD = 0xFF;
	
    while(1)
    {
		unsigned short us_tempWeight = 0; // init weight
		unsigned char us_setBits = 0x00; //init bits
		us_tempWeight = (((us_tempWeight | PIND) << 1 )| (PINB & 0x01)); // set weight
		
		if (us_tempWeight >= 70)
		{
			us_setBits = SetBit(us_setBits, 1, 1);
			
		}else
		{
			us_setBits = SetBit(us_setBits, 1, 0);
		}
		
		if ((us_tempWeight > 5) && (us_tempWeight < 70))
		{
			us_setBits = SetBit(us_setBits, 2, 1);
		}else if(us_tempWeight <= 5)
		{
			us_setBits = us_setBits & 0x01; 
		}else 
		{
			us_setBits = SetBit(us_setBits, 2, 0);
		}
		PORTB = us_setBits;
    }
}