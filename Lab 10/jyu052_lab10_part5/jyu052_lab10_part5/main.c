//external library
#include <avr/io.h>
#include <avr/interrupt.h>
#include "io.c"
#include "bit.h"
#include "timer.h"
#include "scheduler.h"
#include "keypad_custom.h"


//global variables
unsigned char display_string[32];
unsigned char substr[16];
unsigned char substr2[16];
unsigned char front = 0;

unsigned char x					= 0x00;
unsigned char i_count			= 16;
unsigned char i_count2			= 32;
unsigned char Q_content			= 0;

//state machines
#include "KeypadReadSM.h"
#include "Display.h"

int main(void)
{
	DDRB = 0xFF; PORTB = 0x00; // PORTB set to output, outputs init 0s
	DDRC = 0xF0; PORTC = 0x0F; // PC7..4 outputs init 0s, PC3..0 inputs init 1s
	DDRD = 0xFF; PORTD = 0x00;

	/**Set individual task properties********************************/
	unsigned long int Tick1_calc	= 500;
	unsigned long int tempGCD		= findGCD(Tick1_calc, Tick1_calc);
	unsigned long int GCD			= tempGCD;
	unsigned long int Tick1_Period	= Tick1_calc/GCD;	
	static task task1;
	task *tasks[]					= {&task1};
	const unsigned short numTasks	= sizeof(tasks)/sizeof(task*);
	
	/****************************************************************/
	
	/**Set individual task properties**************/
	task1.state						= 0;
	task1.period					= Tick1_Period;
	task1.elapsedTime				= Tick1_Period;
	task1.TickFct					= &Tick2;
	/**********************************************/
	
	
	TimerSet(GCD);
	TimerOn();
	
	LCD_init();
	
	unsigned short i;
	while(1) 
	{
		for(i = 0; i < numTasks; i++)
		{
			if(tasks[i] -> elapsedTime == tasks[i]-> period)
			{
				tasks[i] -> state		= tasks[i] -> TickFct(tasks[i] -> state);
				tasks[i] -> elapsedTime = 0;
			}
			tasks[i] -> elapsedTime += 1;
		}
		while(!TimerFlag);
		TimerFlag = 0;
	}
	return 0;
}