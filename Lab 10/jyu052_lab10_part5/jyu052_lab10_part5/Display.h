/*
 * Tick2.h
 *
 * Created: 8/15/2016 11:31:54 PM
 *  Author: jakex
 */ 


#ifndef TICK2_H_
#define TICK2_H_
#include "ObstacleGenerator.h"

enum displaySM{display_start, display_scroll} displaySM;
int Tick2(int state)
{
	
	unsigned char back = 0;
	switch(state)
	{
		case display_start	 :
		front = 1;
		back = 16;
		ObstacleGenerator();
		
		state =  display_scroll;
		break;
		
		
		case display_scroll  :
			if (front <= 16)
			{
				LCD_ClearScreen();
				for (unsigned char i = 1; i <= 16 ; i++)
				{
					display_string[i] = display_string[i+1];
					LCD_Cursor(1);
					LCD_WriteData(display_string[i]);
					LCD_Cursor(17);
					LCD_WriteData(display_string[15]);
				}
				front++;
			}
			else
			{
				state = display_start;
			}
		break;
		
		default:
			state = display_start; 
		break;
		
	}
	
	return state;
	
}

#endif /* TICK2_H_ */