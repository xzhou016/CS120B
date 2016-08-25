/*
 * Display.h
 *
 * Created: 8/17/2016 9:45:06 PM
 *  Author: jakex
 */ 




#ifndef DISPLAY_H_
#define DISPLAY_H_

unsigned char deathAni;

//display global variables
enum displaySM{display_start,display_wait, display_scroll, display_deathAnimation_X, display_dead} displaySM;
int DisplaySM_Tick(int state)
{
	keypad_value = GetKeypadKey();
	
	//unsigned char back = 0;
	switch(state) //state transition
	{
		case display_start:
			playerIcon						= 0xDB;
			task3.state						= 0;//Task initial state.
			task4.state						= 0;//Task initial state.
			deathAni						= 0;
			 
			state =  display_wait;
		break;
		
		case display_wait:
			if (keypad_value == '1')
			{
				state = display_scroll;
			}
		break;
		
		case display_scroll:
			if (isHit == 0)
			{
				state = display_scroll;
			}
// 			}else if (keypad_value == '1')
// 			{
// 				state = display_start;
// 			}
			
			else 
				state = display_deathAnimation_X;
		break;
		
		case display_deathAnimation_X:
			if (deathAni < 5)
			{
				state = display_deathAnimation_X;
				deathAni++;
			}else
				state = display_dead;
		break;
		
		case display_dead:
			if (keypad_value == '1')
			{
				state = display_start;
			}
		break;
		
		default:
			state = display_start;
		break;
	}
	
	
	switch(state) //state action
	{
		case display_start:
		break;
		
		case display_wait:
			LCD_ClearScreen();
			LCD_DisplayString(1, "   LCD_RACER!   ");
		break;
		
		case display_scroll:
			LCD_ClearScreen();
			LCD_DisplayString(1, row1);
			LCD_DisplayString(17, row2);
			LCD_Cursor(playerPosition);
			//LCD_WriteData(x);
			LCD_WriteData(playerIcon);
		break;
		
		case display_deathAnimation_X:
			task1.state = 0;//Task initial state.
			keypad_value = 'l';
			LCD_ClearScreen();
			LCD_DisplayString(1, row1);
			LCD_DisplayString(17, row2);
			LCD_Cursor(playerPosition);
			if ((deathAni % 2) == 0)
			{
				LCD_WriteData('X');
			} 
			else
			{
				LCD_WriteData(0xDB);
			}
			
		break;
		
		case display_dead:
			LCD_ClearScreen();
			LCD_DisplayString(1, " YOU ARE DEAD:( ");
			clearArray(16);
		break;
		
		default: break;
	}
	
	return state;
	
}




#endif /* DISPLAY_H_ */