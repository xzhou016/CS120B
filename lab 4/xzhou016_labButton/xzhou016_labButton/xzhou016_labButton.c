/*
 * xzhou016_labButton.c
 *
 * Created: 7/28/2016 3:30:31 PM
 * Author : jakex
 */ 

#include <avr/io.h>


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	unsigned char led = 0x00;
	unsigned char button = 0x00;
    /* Replace with your application code */
    while (1) 
    {
		button = ~PINA & 0x01;
		
		if (button)
		{
			led = (led & 0xFC) | 0x01;
		} 
		else
		{
			led = (led & 0xFC) | 0x02;
		}
		
		PORTB = led;
    }
}

