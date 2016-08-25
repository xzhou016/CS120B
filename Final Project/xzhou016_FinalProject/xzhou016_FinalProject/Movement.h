/*
 * Movement.h
 *
 * Created: 8/19/2016 7:05:46 PM
 *  Author: jakex
 */ 


#ifndef MOVEMENT_H_
#define MOVEMENT_H_

enum MovementSM {M_start, M_wait, M_move, M_moveRelease} MovementSM;

unsigned char debounce	= 0;
	
int Movement_Tick(int state)
{
	keypad_value = GetKeypadKey();
	switch(state)
	{
		case M_start:
			state			= M_wait;
		break;
		
		case M_wait:
			 if (keypad_value != '\0')
			{
				state = M_move;
			}
		break;
		
		case M_move:
			state = M_moveRelease;
		break;
		
		case M_moveRelease:
			if (keypad_value == '\0')
			{
				state = M_wait;
			}
		break;
		
		default: 
			state = M_start;
		break;
	}
	
	switch(state)
	{
		case M_start: 
		break;
		
		case M_wait: break;
		
		case M_move:
			if (playerPosition == 16 && keypad_value == 'C')
			{
				playerPosition = 32;
			} 
			if (playerPosition == 32 && keypad_value == 'B')
			{
				playerPosition = 16;
			}
			
			if (keypad_value == '1' && debounce > 5)
			{
				restart = 1;
				debounce = 0;
				//keypad_value = 0;
			}
			
			debounce++;
		break;
		
		case M_moveRelease: 
			//keypad_value = 0;
		break;
		
		default: break;
	}
	return state;
}



#endif /* MOVEMENT_H_ */