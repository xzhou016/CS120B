/*	jyu052_lab3_part1.c -
 *	Name & E-mail:  - Jia Jun Yu, jyu052@ucr.edu
 *	CS Login: jyu052
 *	Partner(s) Name & E-mail:  - Xiao Zhou, xzhou016@ucr.edu 
 *	Lab Section: 21
 *	Assignment: Lab #3  Exercise #1
 *	Exercise Description:
 *	
 *	
 *	I acknowledge all content contained herein, excluding template or example 
 *	code, is my own original work.
 */ 

#include <avr/io.h>

enum LED_States { LED_SMStart, LED_s0, LED_s1 } LED_State;

void TickFct_LED()
{
	switch(LED_State) {   // Transitions
		case LED_SMStart:  // Initial transition
		LED_State = LED_s0;
		break;

		case LED_s0:
		if ((PINA & 0x01) == 0x00) {
			LED_State = LED_s0;
		}
		else if ((PINA & 0x01) == 0x01) {
			LED_State = LED_s1;
		}
		break;

		case LED_s1:
		if ((PINA & 0x01) == 0x01) {
			LED_State = LED_s0;
		}
		else if ((PINA & 0x01) == 0x00) {
			LED_State = LED_s1;
		}
		break;

		default:
		LED_State = LED_SMStart;
		break;
	} // Transitions

	switch(LED_State) {   // State actions
		case LED_s0:
		PORTB = (PORTB | 0x01) & 0x01;
		break;

		case LED_s1:
		PORTB = (PORTB | 0x02) & 0x02;
		break;

		default:
		break;
	} // State actions
}

int main(void)
{
	DDRA = 0x00; PORTA = 0x00;
	DDRB = 0x03; PORTB = 0x00;
	
	 LED_State = LED_SMStart; // Indicates initial call
    while (1) 
    {
		TickFct_LED();
    }
}

