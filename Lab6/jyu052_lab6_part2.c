/* 
* Name: Jia Jun Yu
* Email: jyu052@ucr.edu
* Name: Xiao Zhou
* Email: xzhou016@ucr.edu
* Lab Section: 21
* Assignment: Lab#6  Exercise#2
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
volatile unsigned char tune_freq = 0x00;

enum speakerSM {sm_start, sm_wait, sm_on, sm_off} speakerSM;
enum tunerSM {tuner_start, tuner_wait, tuner_tune, tuner_release} tunerSM;

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

void TickSM2()
{
	unsigned char readPINA = ~PINA & 0x03;
	switch(tunerSM)
	{
		case tuner_start:
		tunerSM = tuner_wait;
		break;
		
		case tuner_wait:
			if (((readPINA & 0x01) == 0x01) ^((readPINA & 0x02) == 0x02) )
			{
				tunerSM = tuner_tune;
			}
			else 
				tunerSM = tuner_wait;
		break;
		
		case tuner_tune:
		tunerSM = tuner_release;
		break;
		
		case tuner_release:
		if (readPINA == 0x00)
		{
			tunerSM = tuner_wait;
		}
		else
			tunerSM = tuner_release;

		break;
		
		default: 
		tunerSM = tuner_start;
		break;	
	}
	
	switch(tunerSM) 
	{
		case tuner_start : 
		break;
		
		case tuner_wait : 
		break;
		
		case tuner_tune :
			if((readPINA & 0x01) == 0x01)
			tune_freq++;
			else if ((readPINA & 0x02) == 0x02 )
			{
				if (tune_freq != 0)
				{
					tune_freq--;
				}

			}
			break;
		
		case tuner_release : 
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
	unsigned char i = 0x00;
    
    while (1) 
    {
		TickSM2();
		if ( i > tune_freq)
		{
			TickSM();
			PORTB = tempB;
			i = 0;
		}
		else i++;

		while(!TimerFlag);

		TimerFlag = 0;
    }
}