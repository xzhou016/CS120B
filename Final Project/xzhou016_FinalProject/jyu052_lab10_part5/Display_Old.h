/*
 * Tick2.h
 *
 * Created: 8/15/2016 11:31:54 PM
 *  Author: jakex
 */ 


#ifndef TICK2_H_
#define TICK2_H_
#include "ObstacleGenerator.h"

//display global variables
unsigned char substr[15];
unsigned char substr2[15];
unsigned char str_index = 0;
unsigned char display_index = 0;

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
			if (str_index < 16)
			{
				state = display_scroll;
			}
			else 
				state = display_start;
		break;
		
		default:
			state = display_start; 
		break;
	}
	
	
	switch(state) //state action
	{
		case display_start: 
			ObstacleGenerator(32);
			//memcpy(substr, &display_string[0], 16);   substr[15] = '\0';
			//memcpy(substr2, &display_string[16], 16); substr2[15] = '\0';
			str_index = 0; display_index = 16;
		break;
		
		case display_scroll:
			LCD_ClearScreen();
			memcpy(substr, &display_string[0], str_index + 1);   substr[str_index] = '\0';
			memcpy(substr2, &display_string[16], str_index + 1); substr2[str_index] = '\0';
			LCD_DisplayString(display_index, substr);
			LCD_DisplayString(display_index + 16, substr2);
			str_index++; display_index--;
		break;
		
		default: break;
	}
	
	return state;
	
}

#endif /* TICK2_H_ */