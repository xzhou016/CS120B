#include <avr/io.h>
#include <avr/interrupt.h>
#include "io.c"
#include "bit.h"
#include "timer.h"
#include "scheduler.h"

/* Returns '\0' if no key pressed, else returns char '1', '2', ... '9', 'A', ...
 If multiple keys pressed, returns leftmost-topmost one
 Keypad must be connected to port C
 Keypad arrangement
        PC4 PC5 PC6 PC7
   col  1   2   3   4
row
PC0 1   1 | 2 | 3 | A
PC1 2   4 | 5 | 6 | B
PC2 3   7 | 8 | 9 | C
PC3 4   * | 0 | # | D
*/

unsigned char GetKeypadKey() {

	PORTC = 0xEF; // Enable col 4 with 0, disable others with 1’s
	asm("nop"); // add a delay to allow PORTC to stabilize before checking
	if (GetBit(PINC,0)==0) { return('1'); }
	if (GetBit(PINC,1)==0) { return('2'); }
	if (GetBit(PINC,2)==0) { return('3'); }
	if (GetBit(PINC,3)==0) { return('A'); }

	// Check keys in col 2
	PORTC = 0xDF; // Enable col 5 with 0, disable others with 1’s
	asm("nop"); // add a delay to allow PORTC to stabilize before checking
	if (GetBit(PINC,0)==0) { return('4'); }
	if (GetBit(PINC,1)==0) { return('5'); }
	if (GetBit(PINC,2)==0) { return('6'); }
	if (GetBit(PINC,3)==0) { return('B'); }

	// Check keys in col 3
	PORTC = 0xBF; // Enable col 6 with 0, disable others with 1’s
	asm("nop"); // add a delay to allow PORTC to stabilize before checking
	if (GetBit(PINC,0)==0) { return('7'); }
	if (GetBit(PINC,1)==0) { return('8'); }
	if (GetBit(PINC,2)==0) { return('9'); }
	if (GetBit(PINC,3)==0) { return('C'); }

	// Check keys in col 4	
	PORTC = 0x7F;
	asm("nop"); // add a delay to allow PORTC to stabilize before checking
	if (GetBit(PINC,0)==0) { return('*'); }
	if (GetBit(PINC,1)==0) { return('0'); }
	if (GetBit(PINC,2)==0) { return('#'); }
	if (GetBit(PINC,3)==0) { return('D'); }

	return('\0'); // default value

}

enum keypadSM{keypad_start, keypad_wait, keypad_read, keypad_release} keypadSM;
long x = 0x00;

int Tick1(int state)
{
	unsigned char keyPress = ~PINC & 0x0F;
	x = GetKeypadKey();
	unsigned char debugVar = 0x00;
	
	switch(state)
	{
		case keypad_start:
		state = keypad_wait;
		break;
		
		case keypad_wait:
		if(keyPress == 0x00)
		state = keypad_wait;
		else
		state = keypad_read;
		break;
		
		case keypad_read: 
			state = keypad_release;

		break;
		
		case keypad_release:
		if(keyPress == 0x00)
		state = keypad_wait;
		else
		state = keypad_release;
		break;
		
		default:
		break;
	}
	
	switch(state)
	{
		case keypad_start:
		break;
		
		case keypad_wait:
		break;
		
		case keypad_read:
		switch (x) {
				case '\0': LCD_ClearScreen(); break; // All 5 LEDs on
				case '1': LCD_DisplayString(1, "1"); break; // hex equivalent
				case '2': LCD_DisplayString(1, "2"); break;
				case '3': LCD_DisplayString(1, "3"); break;
				case 'A': LCD_DisplayString(1, "A"); break;
				case '4': LCD_DisplayString(1, "4"); break;
				case '5': LCD_DisplayString(1, "5"); break;
				case '6': LCD_DisplayString(1, "6"); break;
				case 'B': LCD_DisplayString(1, "B"); break;
				case '7': LCD_DisplayString(1, "7"); break;
				case '8': LCD_DisplayString(1, "8"); break;
				case '9': LCD_DisplayString(1, "9"); break;
				case 'C': LCD_DisplayString(1, "C"); break;
				case '*': LCD_DisplayString(1, "*"); break;
				case '0': LCD_DisplayString(1, "0"); break;
				case '#': LCD_DisplayString(1, "#"); break;
				case 'D': LCD_DisplayString(1, "D"); break;
				default: LCD_ClearScreen(); break;
			}
		break;
		
		case keypad_release:
		break;
		
		default:
		break;
	}
	return state;
}

int main(void)
{
	DDRB = 0xFF; PORTB = 0x00; // PORTB set to output, outputs init 0s
	DDRC = 0xF0; PORTC = 0x0F; // PC7..4 outputs init 0s, PC3..0 inputs init 1s
	DDRD = 0xFF; PORTD = 0x00;
	
	unsigned long int Tick1_calc = 10;
	unsigned long int tempGCD = 1;
	tempGCD = findGCD(Tick1_calc, Tick1_calc);
	
	unsigned long int GCD = tempGCD;
	
	unsigned long int Tick1_Period = Tick1_calc/GCD;
	
	static task task1;
	task *tasks[] = {&task1};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);
	
	task1.state = 1; keypadSM = keypad_start;
	task1.period = Tick1_Period;
	task1.elapsedTime = Tick1_Period;
	task1.TickFct = &Tick1;
	
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
				tasks[i] -> state = tasks[i] -> TickFct(tasks[i] -> state);
				tasks[i] -> elapsedTime = 0;
			}
			tasks[i] -> elapsedTime += 1;
		}
		while(!TimerFlag);
		TimerFlag = 0;
	}
	return 0;
}
