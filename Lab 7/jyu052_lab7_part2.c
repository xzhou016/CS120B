/*
* Name: Jia Jun Yu
* Email: jyu052@ucr.edu
* Name: Xiao Zhou
* Email: xzhou016@ucr.edu
* Lab Section: 21
* Assignment: Lab#7 Exercise#2
*
* I acknowledge all content contained herein, excluding
* template or example code, is my own original work.
*/

#include <avr/io.h>

enum tone_sm {tone_start, tone_wait, tone_set, tone_release0} tone_sm;
enum tone_sm1{tone_start1, tone_play, tone_release, tone_off} tone_sm1;
	
unsigned char tone_selector = 0x00;
double tone_freq = 261.63;

// 0.954 hz is lowest frequency possible with this function,
// based on settings in PWM_on()
// Passing in 0 as the frequency will stop the speaker from generating sound
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

void TickSM1()
{
	unsigned char readPINA = ~PINA & 0x03;
	
	switch(tone_sm)
	{
		case tone_start:
		tone_sm = tone_wait;
		break;
		
		case tone_wait:
		if((readPINA == 0x01) ^ (readPINA == 0x02))
		{
			tone_sm = tone_set;
		}
		else
		{
			tone_sm = tone_wait;
		}
		break;
		
		case tone_set:
		tone_sm = tone_release0;
		break;
		
		case tone_release0 : 
			if (readPINA == 0x01 || readPINA == 0x02)
			{
				tone_sm = tone_release0;
			}else
				tone_sm = tone_wait;
		break;
		
		default:
		tone_sm = tone_start;
		break;
	}
	switch(tone_sm)
	{
		case tone_start:
		break;
		
		case tone_wait:
		break;
		
		case tone_set:
		if (readPINA == 0x01 && tone_selector < 7)
		{
			tone_selector++;
		}
		else if (readPINA == 0x02 && tone_selector > 0)
		{
			tone_selector--;
		}
		
		if (tone_selector == 0) //c4
		{
			tone_freq =  261.63;
		}
		else if (tone_selector == 1) //d
		{
			tone_freq = 293.66;
		}
		else if (tone_selector == 2) //e
		{
			tone_freq = 329.63;
		}
		else if (tone_selector == 3) //f
		{
			tone_freq = 349.23;
		}
		else if (tone_selector == 4) //g
		{
			tone_freq = 392.00;
		}
		else if (tone_selector == 5) //a
		{
			tone_freq = 440;
		}
		else if (tone_selector == 6) //b
		{
			tone_freq = 493.88;
		}
		else if (tone_selector == 7) //c5
		{
			tone_freq = 523.25;
		}
		else
		break;
		
		case tone_release0:
		break;
		
		default:
		break;
		
	}
}

void TickSM2()
{
	unsigned char readPINA = ~PINA & 0x04;
	switch(tone_sm1)
	{
		case tone_start1:
		if (readPINA == 0x04)
		{
			tone_sm1 = tone_play;
		}
		else 
		tone_sm1 = tone_start1;
		break;
		
		case tone_play:
		if (readPINA == 0x04)
		{
			tone_sm1= tone_play;
		}
		else
			tone_sm1 = tone_release;
		break;
		
		case tone_release:
		if (readPINA == 0x00)
		{
			tone_sm1= tone_release;
		}
		else
		tone_sm1 = tone_off;
		break;
		
		case tone_off:
		if (readPINA == 0x04)
		{
			tone_sm1= tone_off;
		}
		else
		tone_sm1 = tone_start1;
		break;
		
		default: 
		tone_sm1 = tone_start1;
		break;
	}
	
	switch(tone_sm1) 
	{
		case tone_start1: 
		set_PWM(0);
		break;
		
		case tone_play:
		break;
		
		case tone_release:
		set_PWM(tone_freq);
		break;
		
		case tone_off:
		set_PWM(0);
		break;
		
		default: 
		break;
	}
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	PWM_on();
	
	while (1)
	{
		TickSM1();
		TickSM2();
	}
	
	return 1;
}

