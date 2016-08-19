/*	xzhou016_lab4_part2.c -
 *	Name & E-mail:  - Xiao Zhou, xzhou016@ucr.edu
 *	CS Login: xzhou016
 *	Partner(s) Name & E-mail:  - Jia Jun Yu, jyu052@ucr.edu
 *	Lab Section: 21
 *	Assignment: Lab #4  Exercise #2
 *	Exercise Description:
 *	
 *	
 *	I acknowledge all content contained herein, excluding template or example 
 *	code, is my own original work.
 */ 

#include <avr/io.h>

enum Count_States {SM_START, SM_INIT, SM_WAIT, INCREMENT_S0, INC_RELEASE, DECREMENT_S1, DEC_RELEASE } Count_States;
unsigned char setPortC = 0x00;

void TickCount()
{
	unsigned char setPinA = ~PINA & 0x03;
	switch(Count_States) {   // Transitions
		case SM_START:  // Initial transition
		Count_States = SM_INIT;
		break;
		
		case SM_INIT:  // Initial transition
		Count_States = SM_WAIT;
		break;

		case SM_WAIT:
		if (((setPinA & 0x01) == 0x01 ) && ((setPinA & 0x02) == 0x00 ) && (setPortC< 0x09)) {
			Count_States = INCREMENT_S0;
		}
		else if (((setPinA & 0x02) == 0x02 ) && ((setPinA & 0x01) == 0x00 && (setPortC > 0x00) )) {
			Count_States = DECREMENT_S1;
		}
		else if (((setPinA & 0x01) == 0x01 ) && ((setPinA & 0x02) == 0x02 )) {
			Count_States = SM_INIT;
		}
		else if (((setPinA & 0x01) == 0x00 ) && ((setPinA & 0x02) == 0x00 )) {
			Count_States = SM_WAIT;
		}
		break;
		
		case INCREMENT_S0:
		Count_States = INC_RELEASE;
		break;

		case INC_RELEASE:
		if (((setPinA & 0x01) == 0x01 )) {
			Count_States = INC_RELEASE;
		}
		else if (((setPinA & 0x01) == 0x00 )) {
			Count_States = SM_WAIT;
		}
		break;
		
		case DECREMENT_S1:
		Count_States = DEC_RELEASE;
		break;
		
		case DEC_RELEASE:
		if (((setPinA & 0x02) == 0x02 )) {
			Count_States = DEC_RELEASE;
		}
		else if (((setPinA & 0x00) == 0x00 )) {
			Count_States = SM_WAIT;
		}
		break;

		default:
		Count_States = SM_START;
		break;
	} // Transitions

	switch(Count_States) {   // State actions
		case SM_INIT:
		setPortC = 0x00;
		break;

		case SM_WAIT:
		break;
		
		case INCREMENT_S0:
		setPortC = setPortC + 0x01;
		break;
		
		case INC_RELEASE:
		break;
		
		case DECREMENT_S1:
		setPortC = setPortC - 0x01;
		break;
		
		case DEC_RELEASE:
		break;

		default:
		break;
	} // State actions
	
	 PORTC = setPortC;
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	
	Count_States = SM_START; // Indicates initial call
	while (1)
	{
		TickCount();
	}
}