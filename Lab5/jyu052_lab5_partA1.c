/* 
* Name: Jia Jun Yu
* Email: jyu052@ucr.edu
* Name: Xiao Zhou
* Email: xzhou016@ucr.edu
* Lab Section: 21
* Assignment: Lab#5  Exercise#A1
*
* I acknowledge all content contained herein, excluding 
* template or example code, is my own original work.
*/

#include <avr/io.h>
#include <avr/interrupt.h>

enum ledthing {led_start, led_0, led_1, led_2} ledthing;

volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

unsigned char tmpC = 0x00;

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

void TickLED()
{
	switch(ledthing)
	{
		case led_start:
		ledthing = led_0;
		break;
		
		case led_0:
		ledthing = led_1;
		break;
		
		case led_1:
		ledthing = led_2;
		break;
		
		case led_2:
		ledthing = led_0;
		break;
		
		default:
		ledthing = led_start;
		break;
	}
	
	switch(ledthing)
	{
		case led_start:
		break;
		
		case led_0:
		tmpC = (tmpC | 0x07) & 0x01;
		break;
		
		case led_1:
		tmpC = (tmpC | 0x07) & 0x02;
		break;
		
		case led_2:
		tmpC = (tmpC | 0x07) & 0x04;
		break;
		
		default:
		break;
	}
}

int main(void)
{
    DDRC = 0xFF;
    PORTC = 0x00;
    TimerSet(1000);
    TimerOn();
    while (1) 
    {
		TickLED();
		PORTC = tmpC;
		while(!TimerFlag);
		TimerFlag = 0;
    }
}

