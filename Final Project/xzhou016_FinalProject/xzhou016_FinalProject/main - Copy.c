#include <avr/io.h>
#include <avr/interrupt.h>
#include "io.c"
#include "bit.h"
#include "timer.h"
#include "scheduler.h"
//#include "queue.h"

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

unsigned char diplay_string[] = {"People don't think universe work its way, but it do. - Newton"};
unsigned char substr[16]; 
unsigned char front = 0x00;
unsigned char back =  15;
unsigned char x = 0x00;
unsigned char i_count = 0;
unsigned char Q_content = 0;

enum keypadSM{keypad_start, keypad_wait, keypad_read, keypad_release} keypadSM;
int Tick1(int state)
{
	unsigned char keyPress = ~PINC & 0x0F;
	x = GetKeypadKey();
	
	switch(state)
	{
		case keypad_start:
		LCD_DisplayString(1, "People don't think universe work its way, but it do. - Newton");
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
				case '2': LCD_DisplayString(2, "2"); break;
				case '3': LCD_DisplayString(3, "3"); break;
				case 'A': LCD_DisplayString(4, "A"); break;
				case '4': LCD_DisplayString(5, "4"); break;
				case '5': LCD_DisplayString(6, "5"); break;
				case '6': LCD_DisplayString(7, "6"); break;
				case 'B': LCD_DisplayString(8, "B"); break;
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
			//if (i_count < )
			{
			}
		break;
		
		case keypad_release:
		break;
		
		default:
		break;
	}
	return state;
}

enum displaySM{display_start, display_wait, display_scroll} displaySM;
int Tick2(int state)
{
	
	switch(state)
	{
		case display_start	 : 
			front = 0, back = 15;
			state =  display_wait; break;
		case display_wait	 : 
			state = display_scroll; break;
		case display_scroll  : 
			if (back <= 61)
			{
				memcpy( substr, &diplay_string[front], 16);
				substr[back] = '\0';
				LCD_DisplayString(1, substr);
				LCD_DisplayString(17,substr);
				front++; back++;
				LCD_Cursor(1);

	
				state = display_scroll;
			} 
			else
			{
				state = display_start;
			}
			break;
		default: 
			state = display_start; break;
		
	}
	
}

int main(void)
{
	DDRB = 0xFF; PORTB = 0x00; // PORTB set to output, outputs init 0s
	DDRC = 0xF0; PORTC = 0x0F; // PC7..4 outputs init 0s, PC3..0 inputs init 1s
	DDRD = 0xFF; PORTD = 0x00;
	//Queue myQ = QueueInit(64);
	//unsigned char error = QueueEnqueue(myQ, diplay_string[i_count]);
	//Q_content = QueueDequeue(myQ);
	
	unsigned long int Tick1_calc = 250;
	unsigned long int tempGCD = 1;
	tempGCD = findGCD(Tick1_calc, Tick1_calc);
	
	unsigned long int GCD = tempGCD;
	
	unsigned long int Tick1_Period = Tick1_calc/GCD;
	
	static task task1;
	task *tasks[] = {&task1};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);
	
	task1.state = 0;
	task1.period = Tick1_Period;
	task1.elapsedTime = Tick1_Period;
	task1.TickFct = &Tick2;
	
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