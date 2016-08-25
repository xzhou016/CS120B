/*
 * AI.h
 *
 * Created: 8/25/2016 9:07:14 AM
 *  Author: jakex
 */ 


#ifndef AI_H_
#define AI_H_
enum AISM {AI_start, AI_checkPos, AI_Move} AISM;
	
int AI_Tick(int state) 
{
	switch(state)
	{
		case AI_start:
			state = AI_checkPos;
		break;
		
		case AI_checkPos:
			if (playerPosition != AIPosition)
			{
				state = AI_Move;
			}
		break;
		
		case AI_Move:
			state = AI_checkPos;
		break;
		
		default: 
			state = AI_start;
		break;
	}
	
	switch(state) 
	{
		case AI_start: break;
		
		case AI_checkPos:
			
		break;
		
		case AI_Move:
			AIPosition = playerPosition - 15;
		break;
		
		default: break;
	}
	

	return state;	
}
#endif /* AI_H_ */