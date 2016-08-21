/*
 * Display.h
 *
 * Created: 8/17/2016 9:45:06 PM
 *  Author: jakex
 */ 


#ifndef DISPLAY_H_
#define DISPLAY_H_


//display global variables

enum displaySM{display_start, display_scroll} displaySM;
int DisplaySM_Tick(int state)
{
	
	
	//unsigned char back = 0;
	switch(state) //state transition
	{
		case display_start:
			state =  display_scroll;
		break;
		
		
		case display_scroll:
			state = display_scroll;
		break;
		
		default:
			state = display_start;
		break;
	}
	
	
	switch(state) //state action
	{
		case display_start:
		break;
		
		case display_scroll:
			LCD_ClearScreen();
			//LCD_Cursor(16);
			if (playerPosition == 16)
			{
				row1[15] = x;
			}else if (playerPosition == 32)
			{
				row2[15] = x;
			}
			 
			LCD_DisplayString(1, row1);
			LCD_DisplayString(17, row2);
			//LCD_Cursor(playerPosition);
			//LCD_WriteData(x);
			//LCD_WriteData(0xDB);
		break;
		
		default: break;
	}
	
	return state;
	
}




#endif /* DISPLAY_H_ */