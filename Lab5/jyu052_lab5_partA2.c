/* 
* Name: Jia Jun Yu
* Email: jyu052@ucr.edu
* Name: Xiao Zhou
* Email: xzhou016@ucr.edu
* Lab Section: 21
* Assignment: Lab#5  Exercise#A2
*
* I acknowledge all content contained herein, excluding 
* template or example code, is my own original work.
*/

#include <avr/io.h>
#include <avr/interrupt.h>

enum ledthing {led_start, led_0, led_1, led_2, led_press, led_pause} ledthing;

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
	unsigned char setPinA = ~PINA & 0x01;
	switch(ledthing)
	{
		case led_start:
		ledthing = led_0;
		break;
		
		case led_0:
		if((setPinA & 0x01) == 0x00)
		ledthing = led_1;
		else
		ledthing = led_pause;
		break;
		
		case led_1:
		if((setPinA & 0x01) == 0x00)
		ledthing = led_2;
		else
		ledthing = led_pause;
		break;
		
		case led_2:
		if((setPinA & 0x01) == 0x00)
		ledthing = led_0;
		else
		ledthing = led_pause;
		break;
		
		case led_press:
		if((setPinA & 0x01) == 0x01)
		ledthing = led_press;
		else
		ledthing = led_pause;
		break;
		
		case led_pause:
		if((tmpC & 0x0F) == 0x01 && setPinA == 0x01)
		{
			ledthing = led_0;
		}
		else if ((tmpC & 0x0F) == 0x02 && setPinA == 0x01)
		{
			ledthing = led_1;
		}
		else if ((tmpC & 0x0F) == 0x04 && setPinA == 0x01)
		{
			ledthing = led_2;
		}
		else if (setPinA == 0x00)
		{
			ledthing = led_pause;
		}
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
		
		case led_press:
		break;
		
		case led_pause:
		break;
		
		default:
		break;
	}
}

int main(void)
{
	DDRA = 0x00;
	PORTA = 0xFF;
    DDRC = 0xFF;
    PORTC = 0x00;
    TimerSet(300);
    TimerOn();
    while (1) 
    {
		
		PORTC = tmpC;
		TickLED();
		while(!TimerFlag);
		TimerFlag = 0;
    }
}

