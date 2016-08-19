/* 
* Name: Jia Jun Yu
* Email: jyu052@ucr.edu
* Name: Xiao Zhou
* Email: xzhou016@ucr.edu
* Lab Section: 21
* Assignment: Lab#6  Exercise#1
*
* I acknowledge all content contained herein, excluding 
* template or example code, is my own original work.
*/

#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

unsigned char tempB = 0x00;

enum speakerSM {sm_start, sm_wait, sm_on, sm_off} speakerSM;

void TimerOn()
{
	TCCR1B = 0x0B;
	
	OCR1A = 125;
	
	TIMSK1 = 0x02;
	
	TCNT1 = 0;
	
	_avr_timer_cntcurr = _avr_timer_M;
	
	SREG |= 0x80;
}

void TimerOff()
{
	TCCR1B = 0x00;
}

void TimerISR()
{
	TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect)
{
	_avr_timer_cntcurr--;
	if(_avr_timer_cntcurr == 0)
	{
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

void TimerSet(unsigned long M)
{
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

void TickSM()
{
	unsigned char setPINA = ~PINA & 0x04;
	switch(speakerSM)
	{
		case sm_start:
		speakerSM = sm_wait;
		break;
		
		case sm_wait:
		if(setPINA == 0x04)
		speakerSM = sm_on;
		else
		speakerSM = sm_wait;
		break;
		
		case sm_on:
		speakerSM = sm_off;
		break;
		
		case sm_off:
		speakerSM = sm_wait;
		break;
		
		default:
		speakerSM = sm_start;
		break;
	}
	
	switch(speakerSM)
	{
		case sm_start:
		break;
		
		case sm_wait:
		tempB = 0x00;
		break;
		
		case sm_on:
		tempB = (tempB | 0x10) & 0x10;
		break;
		
		case sm_off:
		tempB = 0x00;
		break;
		
		default:
		break;
	}
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	TimerSet(1);
	TimerOn();
    
    while (1) 
    {
		PORTB = tempB;
		TickSM();
		while(!TimerFlag);
		TimerFlag = 0;
    }
}