/*
* Name: Jia Jun Yu
* Email: jyu052@ucr.edu
* Name: Xiao Zhou
* Email: xzhou016@ucr.edu
* Lab Section: 21
* Assignment: Lab#7 Exercise#3
*
* I acknowledge all content contained herein, excluding
* template or example code, is my own original work.
*/

#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

unsigned char holdCount = 0;
unsigned char totalCount = 0;
unsigned char nextNote = 0;

double notes[10] = {0, 261.63, 293.66, 329.63, 349.23, 392, 440, 493.88, 523.25, 196};

// Ode to Joy
unsigned char cMelody[] = {3, 0, 3, 0, 4, 0, 5, 0, 5, 0, 4, 0, 3, 0, 2, 0, 1, 0, 1, 0, 2, 0, 3, 0, 3, 0, 2, 0, 2, 0,
						   3, 0, 3, 0, 4, 0, 5, 0, 5, 0, 4, 0, 3, 0, 2, 0, 1, 0, 1, 0, 2, 0, 3, 0, 2, 0, 1, 0, 1, 0,
						   2, 0, 2, 0, 3, 0, 1, 0, 2, 0, 3, 0, 4, 0, 3, 0, 1, 0, 2, 0, 3, 0, 4, 0, 3, 0, 2, 0, 1, 0, 2, 0, 9, 0,
						   3, 0, 3, 0, 4, 0, 5, 0, 5, 0, 4, 0, 3, 0, 2, 0, 1, 0, 1, 0, 2, 0, 3, 0, 2, 0, 1, 0, 1, 0};
unsigned char holdTime[] = {8, 0, 8, 0, 8, 0, 8, 0, 8, 0, 8, 0, 8, 0, 8, 0, 8, 0, 8, 0, 8, 0, 8, 0, 12, 0, 4, 0, 16, 0,
							8, 0, 8, 0, 8, 0, 8, 0, 8, 0, 8, 0, 8, 0, 8, 0, 8, 0, 8, 0, 8, 0, 8, 0, 12, 0, 4, 0, 16, 0,
							8, 0, 8, 0, 8, 0, 8, 0, 8, 0, 4, 0, 4, 0, 8, 0, 8, 0, 8, 0, 4, 0, 4, 0, 8, 0, 8, 0, 8, 0, 8, 0, 16, 0,		
							8, 0, 8, 0, 8, 0, 8, 0, 8, 0, 8, 0, 8, 0, 8, 0, 8, 0, 8, 0, 8, 0, 8, 0, 12, 0, 4, 0, 16, 0};
unsigned short totalTime = 124;



/* John Cena opening
unsigned char cMelody[] = {6, 0, 7, 0, 5, 0, 6, 0, 8, 0, 7, 0, 5, 0, 6, 0};
unsigned char holdTime[] = {8, 0, 2, 0, 2, 0, 24, 0, 8, 0, 2, 0, 2, 0, 24, 0};
unsigned short totalTime = 16;
*/


/* Darude Sandstorm
unsigned char cMelody[] = {1,0,1,0,1,0,1,0,1,0,1,0,4,0,4,0,4,0,4,0,3,0,3,0,3,0,3,0,7,0,1,0,1,0,1,0,1,0,1,0,1,0,4,0,1,0,1,0,1,0,1,0,1,0,1,0,4,0};
unsigned char holdTime[] = {4,0,6,0,4,0,4,0,6,0,4,0,4,0,2,0,4,0,4,0,4,0,6,0,2,0,4,0,4,0,6,0,2,0,4,0,4,0,2,0,4,0,4,0,6,0,2,0,4,0,4,0,2,0,4,0,4,0};
unsigned short totalTime = 58;
*/


/* Skyrim
unsigned char cMelody[] = {5,0,6,0,7,0,7,0,8,0,2,0,2,0,4,0,8,0,7,0,6,0,5,0,5,0,6,0,7,0,7,0,8,0,2,0,2,0,4,0,5,0,4,0,6,0,5,0};
unsigned char holdTime[] = {4,0,4,0,32,0,4,0,4,0,32,0,4,0,4,0,32,0,4,0,4,0,32,0,4,0,4,0,32,0,4,0,4,0,32,0,4,0,4,0,40,0,4,0,4,0,40,0};
unsigned short totalTime = 48;
*/


/* Surprise
unsigned char cMelody[] = {7,0,3,0,7,0,8,0,2,0,5,0,5,0,8,0,7,0,6,0,7,0,3,0,3,0,4,0,4,0,5,0,6,0,6,0,7,0,8,0,2,0,3,0,4,0};
unsigned char holdTime[] = {8,0,24,0,8,0,4,0,12,0,8,0,8,0,24,0,12,0,8,0,24,0,8,0,8,0,24,0,24,0,24,0,12,0,6,0,6,0,24,0,6,0,32,0,0,0};
unsigned short totalTime = 46;
*/

enum tone_sm1 {tone_start, tone_first, tone_play} tone_sm1;


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

void set_PWM(double frequency) {
	static double current_frequency; // Keeps track of the currently set frequency
	// Will only update the registers when the frequency changes, otherwise allows
	// music to play uninterrupted.
	if (frequency != current_frequency) {
		if (!frequency) { TCCR3B &= 0x08; } //stops timer/counter
		else { TCCR3B |= 0x03; } // resumes/continues timer/counter
		// prevents OCR3A from overflowing, using prescaler 64
		// 0.954 is smallest frequency that will not result in overflow
		if (frequency < 0.954) { OCR3A = 0xFFFF; }
		// prevents OCR3A from underflowing, using prescaler 64
		// 31250 is largest frequency that will not result in underflow
		else if (frequency > 31250) { OCR3A = 0x0000; }
		// set OCR3A based on desired frequency
		else { OCR3A = (short)(8000000 / (128 * frequency)) - 1; }
		TCNT3 = 0; // resets counter
		current_frequency = frequency; // Updates the current frequency
	}
}
void PWM_on() {
	TCCR3A = (1 << COM3A0);
	// COM3A0: Toggle PB6 on compare match between counter and OCR3A
	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
	// WGM32: When counter (TCNT3) matches OCR3A, reset counter
	// CS31 & CS30: Set a prescaler of 64
	set_PWM(0);
}
void PWM_off() {
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}

void TickSM()
{
	unsigned char readPINA = ~PINA & 0x01;
	switch(tone_sm1)
	{
		case tone_start:
		if (readPINA == 0x01)
		tone_sm1 = tone_first;
		else
		tone_sm1 = tone_start;
		break;
		
		case tone_first:
		tone_sm1 = tone_play;
		break;
	
		case tone_play:
		if(totalCount < totalTime)
		tone_sm1 = tone_play;
		else
		tone_sm1 = tone_start;
		break;
		
		default:
		tone_sm1 = tone_start;
		break;
	}
	
	switch(tone_sm1)
	{
		case tone_start:
		set_PWM(0);
		totalCount = 0;
		holdCount = 0;
		nextNote = 0;
		break;
		
		case tone_first:
		set_PWM(notes[cMelody[nextNote]]);
		totalCount++;
		break;
		
		case tone_play:
		if(holdCount >= holdTime[nextNote])
		{
			nextNote++;
			set_PWM(notes[cMelody[nextNote]]);
			holdCount = 0;
			totalCount++;
		}
		else
		{
			holdCount++;
		}
		break;
		
		default:
		break;
	}
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	TimerSet(30);
	TimerOn();
	
	PWM_on();
	
    while (1) 
    {
			TickSM();
			while(!TimerFlag);
			TimerFlag = 0;
    }
}

