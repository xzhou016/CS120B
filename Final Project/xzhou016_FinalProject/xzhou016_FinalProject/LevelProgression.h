/*
 * LevelProgression.h
 *
 * Created: 8/24/2016 11:16:09 PM
 *  Author: jakex
 */ 


#ifndef LEVELPROGRESSION_H_
#define LEVELPROGRESSION_H_

enum LevelProgressionSM {LP_start, LP_difficultySet} LevelProgressionSM;

int LevelProgression_Tick(int state)
{
	switch(state)//state transition
	{
		case LP_start: 
			if (beginGenerate == 1)
			{
				state = LP_difficultySet;
			}
		break;
		
		case LP_difficultySet:
			if (beginGenerate == 0)
			{
				state = LP_start;
			}
		break;
		
		default:
			state = LP_start;
		break;
	}
	
	switch(state)
	{
		case LP_start:
			object_generate_prob = 20;
		break;
		
		case LP_difficultySet:
			if (object_generate_prob > 2)
			{
				object_generate_prob--;
			}
		break;
		
		default:
		break;
	}
	
	return state;
}

#endif /* LEVELPROGRESSION_H_ */