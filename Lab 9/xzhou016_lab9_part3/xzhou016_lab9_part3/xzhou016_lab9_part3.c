/*
 * jyu052_lab9_part3.c
 *
 * Created: 8/10/2016 11:56:35 AM
 * Author : Jia Yu
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

enum sm1{sm1_start, sm1_wait, sm1_inc, sm1_dec} sm1;
enum sm2{sm2_start, sm2_wait, sm2_hold} sm2;
	
	
unsigned char setPinA = 0x00;
unsigned char tempB = 0x00;
unsigned char total = 0x00;
unsigned char i1 = 0x00;
unsigned char i2 = 0x00;
unsigned char counter = 0x00;

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

void Tick1()
{
	setPinA = ~PINA & 0x03;
	switch(sm1)
	{
		case sm1_start:
			sm1 = sm1_wait;
			if (((setPinA & 0x01) == 0x01 ) && ((setPinA & 0x02) == 0x00 ) && (total < 0x09)) 
			{
				sm1 = sm1_inc;
			}
			else if (((setPinA & 0x02) == 0x02 ) && ((setPinA & 0x01) == 0x00 && (total > 0x00) )) 
			{
				sm1 = sm1_dec;
			}
			else if (((setPinA & 0x01) == 0x00 ) && ((setPinA & 0x02) == 0x00 )) 
			{
				sm1 = sm1_wait;
			}
			else if (setPinA == 0x03)
			{
				sm1 = sm1_start;
			}
		break;
		
		case sm1_wait:
			if (((setPinA & 0x01) == 0x01 ) && ((setPinA & 0x02) == 0x02 )) 
			{
				sm1 = sm1_start;
			}
			else if (((setPinA & 0x01) == 0x01 ) && ((setPinA & 0x02) == 0x00 ) && (total < 0x09)) 
			{
				sm1 = sm1_inc;
			}
			else if (((setPinA & 0x02) == 0x02 ) && ((setPinA & 0x01) == 0x00 && (total > 0x00) )) 
			{
				sm1 = sm1_dec;
			}
			else if (((setPinA & 0x01) == 0x00 ) && ((setPinA & 0x02) == 0x00 )) 
			{
				sm1 = sm1_wait;
			}
			else if (setPinA == 0x03)
			{
				sm1 = sm1_start;
			}
		break;
		
		case sm1_inc:
			sm1 = sm1_wait;
		break;
		
		case sm1_dec:
			sm1 = sm1_wait;
		break;
		
		default:
			sm1 = sm1_start;
		break;
	}
	
	switch(sm1)
	{
		case sm1_start:
			total = 0;
		break;
		
		case sm1_wait:
		break;
		
		case sm1_inc:
			total++;
		break;
		
		case sm1_dec:
			total--;
		break;
		
		default:
		break;
	}
}

void Tick2()
{
	unsigned char readPINA = ~PINA & 0x03;
				  setPinA  = ~PINA & 0x03; 
	
	switch(sm2)
	{
		case sm2_start:
			sm2 = sm2_wait;
		break;
		
		case sm2_wait:
			if(readPINA == 0x01 || readPINA == 0x02 || readPINA == 0x03)
			sm2 = sm2_hold;
			else
			sm2 = sm2_wait;
		break;
		
		case sm2_hold:
			if(readPINA == 0x01 || readPINA == 0x02 || readPINA == 0x03)
				sm2 = sm2_hold;
			else
				sm2 = sm2_start;
		break;
		
		default:
		sm2 = sm2_start;
		break;
	}
	
	switch(sm2)
	{
		case sm2_start:
			i1 = 0;
		break;
		
		case sm2_wait:

		break;
		
		case sm2_hold:
			if (i1 < 2)
			{
				counter = 0x01;
			}else if (i1 >= 2 && i1 <= 30)
			{
				counter = 0x0A;
			}else if (i1 > 30)
			{
				counter = 0x04;
				i1 = 30;
			}
			i1++;
		break;
		
		default:
		break;
	}
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	TimerSet(100);
	TimerOn();
	
	sm1 = sm1_start;
	sm2 = sm2_start;
	
    while (1) 
    {
		Tick2(); //call second sm first to set timer for inc & dec
		
		//will only call when buttons are pressed and loop == counter
		if (i2 >= counter && (setPinA == 0x01 || setPinA == 0x02 || setPinA == 0x03)) 
		{
			Tick1();
			i2 = 1;
		}else 
			i2++; //increment to match counter to do operation
		
		if (sm2 == sm2_start) //reset main loop counter
		{
			i2 = 0;
		}


		PORTB = total;
		while(!TimerFlag);
		TimerFlag = 0;
    }
}

