/* 
* Name: Jia Jun Yu
* Email: jyu052@ucr.edu
* Name: Xiao Zhou
* Email: xzhou016@ucr.edu
* Lab Section: 21
* Assignment: Lab#9 Exercise#1
*
* I acknowledge all content contained herein, excluding 
* template or example code, is my own original work.
*/

#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

unsigned char ledshift = 0x00;
unsigned char ledblink = 0x00;

enum threeLED {sm1_start, sm1_init, sm1_shift} threeLED;
enum blinkLED {sm2_start, sm2_off, sm2_on} blinkLED;
enum combineLED {sm3_start, sm3_init} combinedLED;

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
	switch(threeLED)
	{
		case sm1_start:
		threeLED = sm1_init;
		break;
		
		case sm1_init:
		threeLED = sm1_shift;
		break;
		
		case sm1_shift:
		if((ledshift & 0x04) == 0x04)
		threeLED = sm1_init;
		break;
		
		default:
		threeLED = sm1_start;
		break;
	}
	
	switch(threeLED)
	{
		case sm1_start:
		ledshift = 0x00;
		break;
		
		case sm1_init:
		ledshift = 0x01;
		break;
		
		case sm1_shift:
		ledshift = ledshift << 1;
		break;
		
		default:
		break;
	}
}

void Tick2()
{
	switch(blinkLED)
	{
		case sm2_start:
		blinkLED = sm1_init;
		break;
		
		case sm2_off:
		blinkLED = sm2_on;
		break;
		
		case sm2_on:
		blinkLED = sm2_off;
		break;
		
		default:
		blinkLED = sm2_start;
		break;
	}
	
	switch(blinkLED)
	{
		case sm2_start:
		break;
		
		case sm2_off:
		ledblink = 0x00;
		break;
		
		case sm2_on:
		ledblink = 0x08;
		break;
		
		default:
		break;
	}
}

void Tick3()
{
	switch(combinedLED)
	{
		case sm3_start:
		combinedLED = sm3_init;
		break;
		
		case sm3_init:
		PORTB = ledshift | ledblink;
		combinedLED = sm3_init;
		break;
		
		default:
		combinedLED = sm3_start;
	}
}

int main(void)
{
	DDRB = 0xFF; PORTB = 0x00;
	TimerSet(1000);
	TimerOn();
    
    while (1) 
    {
		Tick1();
		Tick2();
		Tick3();
		while(!TimerFlag);
		TimerFlag = 0;
    }
}