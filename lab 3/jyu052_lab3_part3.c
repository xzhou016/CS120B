 /*	jyu052_lab3_part3.c -
 *	Name & E-mail:  - Jia Jun Yu, jyu052@ucr.edu
 *	CS Login: jyu052
 *	Partner(s) Name & E-mail:  - Xiao Zhou, xzhou016@ucr.edu 
 *	Lab Section: 21
 *	Assignment: Lab #3  Exercise #3
 *	Exercise Description:
 *	
 *	
 *	I acknowledge all content contained herein, excluding template or example 
 *	code, is my own original work.
 */ 

#include <avr/io.h>

enum Lock_States { Lock_Start, Lock_Init, R_Stage1, R_Stage2, Lock_Unlock } Lock_State;

void TickLock()
{
	switch(Lock_State) {   // Transitions
		case Lock_Start:  // Initial transition
		Lock_State = Lock_Init;
		break;

		case Lock_Init:
		if ((PINA & 0x07) == 0x04) {
			Lock_State = R_Stage1;
		}
		else {
			Lock_State = Lock_Init;
		}
		break;

		case R_Stage1:
		if ((PINA & 0x07) == 0x02) {
			Lock_State = R_Stage2;
		}
		else if ((PINA & 0x07) == 0x04) {
			Lock_State = R_Stage1;
		}
		else {
			Lock_State = Lock_Init;
		}
		break;
		
		case R_Stage2:
		if ((PINA & 0x07) == 0x00) {
			Lock_State = Lock_Unlock;
		}
		else if ((PINA & 0x07) == 0x02) {
			Lock_State = R_Stage2;
		}
		break;
		
		case Lock_Unlock:
		if ((PINA & 0xFF) == 0x80) {
			Lock_State = Lock_Init;
		}
		else {
			Lock_State = Lock_Unlock;
		}
		break;

		default:
		Lock_State = Lock_Start;
		break;
	} // Transitions

	switch(Lock_State) {   // State actions
		case Lock_Init:
		PORTB = PINB & 0x00;
		break;
		
		case R_Stage1:
		break;
		
		case R_Stage2:
		break;
		
		case Lock_Unlock:
		PORTB = (PINB | 0x01) & 0x01;
		break;

		default:
		break;
	} // State actions
}

int main(void)
{
	DDRA = 0x00; PORTA = 0x00;
	DDRB = 0x00; PORTB = 0x00;
	
	 PORTB = 0x00;              // Initialize outputs
	 Lock_State = Lock_Start; // Indicates initial call
    while (1) 
    {
		TickLock();
    }
}

