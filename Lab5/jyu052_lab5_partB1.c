/* 
* Name: Jia Jun Yu
* Email: jyu052@ucr.edu
* Name: Xiao Zhou
* Email: xzhou016@ucr.edu
* Lab Section: 21
* Assignment: Lab#5  Exercise#B1
*
* I acknowledge all content contained herein, excluding 
* template or example code, is my own original work.
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "io.c"

enum Count_States {SM_START, SM_INIT, SM_WAIT, INCREMENT_S0, DECREMENT_S1,} Count_States;
unsigned char setPortC = 0x00;
unsigned char setPinA = 0x00;

volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

unsigned short i_counter = 0;

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

void TickCount()
{
	switch(Count_States) {   // Transitions
		case SM_START:  // Initial transition
		Count_States = SM_INIT;
		break;
		
		case SM_INIT:  // Initial transition
		Count_States = SM_WAIT;
		break;

		case SM_WAIT:
		if (((setPinA & 0x01) == 0x01 ) && ((setPinA & 0x02) == 0x02 )) {
			Count_States = SM_INIT;
		}
		else if (((setPinA & 0x01) == 0x00 ) && ((setPinA & 0x02) == 0x00 )) {
			Count_States = SM_WAIT;
		}
		else if (((setPinA & 0x01) == 0x01 ) && ((setPinA & 0x02) == 0x00 ) && (setPortC< 0x09)) {
			Count_States = INCREMENT_S0;
		}
		else if (((setPinA & 0x02) == 0x02 ) && ((setPinA & 0x01) == 0x00 && (setPortC > 0x00) )) {
			Count_States = DECREMENT_S1;
		}
		break;
		
		case INCREMENT_S0:
		if(((setPinA & 0x01) == 0x01 ) && ((setPinA & 0x02) == 0x00 ) && (setPortC < 0x09))
		{
				Count_States = INCREMENT_S0;
		}
		else if (((setPinA & 0x01) == 0x00 )) 
		{
			Count_States = SM_WAIT;
		}
		break;
		
		case DECREMENT_S1:
		if (((setPinA & 0x02) == 0x02 ) && ((setPinA & 0x01) == 0x00 && (setPortC > 0x00) ))
		{
			Count_States = DECREMENT_S1;
		}
		else if (((setPinA & 0x02) == 0x00 )) 
		{
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
		displayNumbers();
		break;
		
		case DECREMENT_S1:
		setPortC = setPortC - 0x01;
		displayNumbers();
		break;

		default:
		break;
	} // State actions
}

void displayNumbers()
{
	if(setPortC == 0x00)
	{
		LCD_DisplayString(1, "0");
	}
	else if(setPortC == 0x01)
	{
		LCD_DisplayString(1, "1");
	}
	else if(setPortC == 0x02)
	{
		LCD_DisplayString(1, "2");
	}
	else if(setPortC == 0x03)
	{
		LCD_DisplayString(1, "3");
	}
	else if(setPortC == 0x04)
	{
		LCD_DisplayString(1, "4");
	}
	else if(setPortC == 0x05)
	{
		LCD_DisplayString(1, "5");
	}
	else if(setPortC == 0x06)
	{
		LCD_DisplayString(1, "6");
	}
	else if(setPortC == 0x07)
	{
		LCD_DisplayString(1, "7");
	}
	else if(setPortC == 0x08)
	{
		LCD_DisplayString(1, "8");
	}
	else if(setPortC == 0x09)
	{
		LCD_DisplayString(1, "9");
	}
}


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00; // LCD data lines
    DDRD = 0xFF; PORTD = 0x00; // LCD control lines
	
	TimerSet(100);
	TimerOn();
	
	Count_States = SM_START;
	
    // Initializes the LCD display
    LCD_init();
	
	displayNumbers();
	
    while(1) 
	{
		setPinA = ~PINA & 0x03;
		if (i_counter > 10)
		{
			TickCount();
			i_counter = 0;	
		}
		else
		i_counter++;
		while(!TimerFlag);
		TimerFlag = 0;
	}
}

