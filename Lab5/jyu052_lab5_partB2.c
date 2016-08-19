/* 
* Name: Jia Jun Yu
* Email: jyu052@ucr.edu
* Name: Xiao Zhou
* Email: xzhou016@ucr.edu
* Lab Section: 21
* Assignment: Lab#5  Exercise#B2
*
* I acknowledge all content contained herein, excluding 
* template or example code, is my own original work.
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "io.c"

enum ledthing {led_start, led_0, led_1, led_2, led_press, led_pause} ledthing;

volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

unsigned char tmpB = 0x00;
unsigned char scoreCount = 0x05;

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

void displayNumbers()
{
	if(scoreCount == 0x00)
	{
		LCD_DisplayString(1, "0");
	}
	else if(scoreCount == 0x01)
	{
		LCD_DisplayString(1, "1");
	}
	else if(scoreCount == 0x02)
	{
		LCD_DisplayString(1, "2");
	}
	else if(scoreCount == 0x03)
	{
		LCD_DisplayString(1, "3");
	}
	else if(scoreCount == 0x04)
	{
		LCD_DisplayString(1, "4");
	}
	else if(scoreCount == 0x05)
	{
		LCD_DisplayString(1, "5");
	}
	else if(scoreCount == 0x06)
	{
		LCD_DisplayString(1, "6");
	}
	else if(scoreCount == 0x07)
	{
		LCD_DisplayString(1, "7");
	}
	else if(scoreCount == 0x08)
	{
		LCD_DisplayString(1, "8");
	}
	else if(scoreCount == 0x09)
	{
		LCD_DisplayString(1, "9");
	}
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
		ledthing = led_press;
		break;
		
		case led_1:
		if((setPinA & 0x01) == 0x00)
		ledthing = led_2;
		else
		ledthing = led_press;
		break;
		
		case led_2:
		if((setPinA & 0x01) == 0x00)
		ledthing = led_0;
		else
		ledthing = led_press;
		break;
		
		case led_press:
		if((setPinA & 0x01) == 0x01)
		ledthing = led_press;
		else
		ledthing = led_pause;
		break;
		
		case led_pause:
		if((tmpB & 0x07) == 0x01 && setPinA == 0x01)
		{
			ledthing = led_0;
		}
		else if ((tmpB & 0x07) == 0x02 && setPinA == 0x01)
		{
			ledthing = led_1;
		}
		else if ((tmpB & 0x07) == 0x04 && setPinA == 0x01)
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
		tmpB = (tmpB | 0x07) & 0x04;
		break;
		
		case led_1:
		tmpB = (tmpB | 0x07) & 0x02;
		break;
		
		case led_2:
		tmpB = (tmpB | 0x07) & 0x01;
		break;
		
		case led_press:
		{
			if (tmpB  == 0x02)
			{
			scoreCount ++;
			displayNumbers();
			}
			else if(tmpB == 0x01 || tmpB  == 0x04)
			{
			scoreCount--;
			displayNumbers();
			}
			
			ledthing = led_pause;
		break;
		}
		
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
	DDRD = 0xFF; 
	PORTD = 0x00; // LCD control lines
	DDRB = 0xFF;
	PORTB = 0x00;
	
    TimerSet(300);
    TimerOn();
	
	LCD_init();
	
	displayNumbers();
    while (1) 
    {
		
		PORTB = tmpB;
		TickLED();
		while(!TimerFlag);
		TimerFlag = 0;
		if(scoreCount >= 0x09)
		{
			LCD_DisplayString(1, "Victory!!!!!!");
			while(1){}
		}

    }
}