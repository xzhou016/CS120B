/* 
* Name: Jia Jun Yu
* Email: jyu052@ucr.edu
* Name: Xiao Zhou
* Email: xzhou016@ucr.edu
* Lab Section: 21
* Assignment: Lab#4 Exercise#1
*
* I acknowledge all content contained herein, excluding 
* template or example code, is my own original work.
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
	
	unsigned char us_led = 0x00;
	unsigned char us_switch = 0x00;
	
	
	while(1)
	{
		us_switch = ~PINA & 0x0F;
		if ((us_switch > 0x0C) && (us_switch <= 0x0F))
		{
			us_led = SetBit(us_led, 0, 1);	
		}else
		{
			us_led = SetBit(us_led, 0, 0); 
		}
		
		if ((us_switch > 0x09) && (us_switch <= 0x0F))
		{
			us_led = SetBit(us_led, 1, 1);
			
		}else
		{
			us_led = SetBit(us_led, 1, 0);
		}
		
		if ((us_switch > 0x06) && (us_switch <= 0x0F))
		{
			us_led = SetBit(us_led, 2, 1);
			
		}else
		{
			us_led = SetBit(us_led, 2, 0);
		}
		
		if ((us_switch > 0x04) && (us_switch <= 0x0F))
		{
			us_led = SetBit(us_led, 3, 1);
			
		}else
		{
			us_led = SetBit(us_led, 3, 0);
		}
		
		if ((us_switch > 0x02) && (us_switch <= 0x0F))
		{
			us_led = SetBit(us_led, 4, 1);
		}else
		{
			us_led = SetBit(us_led, 4, 0);
		}
		
		if ((us_switch > 0x00) && (us_switch <= 0x0F))
		{
			us_led = SetBit(us_led, 5, 1);
		}else
		{
			us_led = SetBit(us_led, 5, 0);
		}
		
		if ((us_switch > 0x00) && (us_switch <= 0x04))
		{
			us_led = SetBit(us_led, 6, 1);
		}else
		{
			us_led = SetBit(us_led, 6, 0);
		}
		
		PORTC = us_led;
	}
}