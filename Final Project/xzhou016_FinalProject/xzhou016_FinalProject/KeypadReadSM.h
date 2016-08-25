/*
 * Tick1.h
 *
 * Created: 8/15/2016 11:30:15 PM
 *  Author: jakex
 */ 


#ifndef TICK1_H_
#define TICK1_H_

enum keypadSM{keypad_start, keypad_wait, keypad_read, keypad_release} keypadSM;
int Tick1(int state)
{
	unsigned char keyPress = ~PINC & 0x0F;
	keypad_value = GetKeypadKey();
	
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
		case keypad_start:	break;
		
		case keypad_wait:	break;
		
		case keypad_read:
			switch (keypad_value )
			 {
				case '\0': LCD_ClearScreen();		 break; // All 5 LEDs on
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
				default	: LCD_ClearScreen();		 break;
			}
		break;
		
		case keypad_release:	break;
		
		default:				break;
	}
	return state;
}



#endif /* TICK1_H_ */