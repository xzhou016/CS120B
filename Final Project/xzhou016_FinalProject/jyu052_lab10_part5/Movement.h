/*
 * Movement.h
 *
 * Created: 8/19/2016 7:05:46 PM
 *  Author: jakex
 */ 


#ifndef MOVEMENT_H_
#define MOVEMENT_H_

enum MovementSM {M_start, M_wait, M_move, M_moveRelease} MovementSM;
	
int Movement_Tick(int state)
{
	x = GetKeypadKey();
	switch(state)
	{
		case M_start:
			state = M_wait;
		break;
		
		case M_wait:
			if (x != '\0')
			{
				state = M_move;
			} 
		break;
		
		case M_move:
			state = M_moveRelease;
		break;
		
		case M_moveRelease:
			if (x == '\0')
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
		case M_start: break;
		
		case M_wait: break;
		
		case M_move:
			if (playerPosition = 16 && x == 'C')
			{
				playerPosition = 32;
			} 
			if (playerPosition = 32 && x == 'B')
			{
				playerPosition = 16;
			}
		break;
		
		case M_moveRelease: break;
		
		default: break;
	}
	
	return state;
}



#endif /* MOVEMENT_H_ */