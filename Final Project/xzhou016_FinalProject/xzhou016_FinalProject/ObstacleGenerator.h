/*
 * ObstacleGenerator.h
 *
 * Created: 8/18/2016 12:14:01 AM
 *  Author: jakex
 */ 


#ifndef OBSTACLEGENERATOR_H_
#define OBSTACLEGENERATOR_H_

void arrayShift(unsigned char shift)
{
	for (unsigned char i = shift ; i > 0; i--)
	{
		row1[i] = row1[i - 1];
		row2[i] = row2[i - 1 ];
	}
	
}

void clearArray(unsigned char arraySize)
{
	for (unsigned char i = 0 ; i < arraySize; i++)
	{
		row1[i] = 32;
		row2[i] = 32;
	}
}

enum ObstacleGeneratorSM {OGSM_start, OGSM_wait, OGSM_generate} ObstacleGeneratorSM;
int ObstacleGeneratorSM_Tick(int state)
{
	switch(state) //state transition
	{
		//keypad_value = GetKeypadKey();
		case OGSM_start: 
			state = OGSM_wait;
		break;
		
		case OGSM_wait:
			if ( restart == 1)
			{
				state = OGSM_start;
			}else if (beginGenerate == 1)
			{
				state = OGSM_generate;
			}
		break;
		
		case OGSM_generate:
			if (restart == 1)
			{
				state = OGSM_start;
			}
			else
			{
				state = OGSM_wait;
			}
		break;
		
		default: 
			state = OGSM_start;
		break;
	}
	
	switch(state) //state actions
	{
		case OGSM_start:
			str_index				= 1;
			object_generate_prob	= 20;
			clearArray(17);
		break;
		
		case OGSM_wait:
			
		break;
		
		case OGSM_generate: 
			//shift data >> 1
			arrayShift(str_index);
			//generate an obstacle then push into first index
			if ((rand() % object_generate_prob) == 1)
			{
				row1[0] = '#';
			}
			else if ((rand() % object_generate_prob) == 1)
			{
				row1[0] = '*';
			}
			else if ((rand() % AI_fire_prob) == 1 && AIPosition == 1)
			{
				row1[0] = '-';
			}
			else if ((rand() % powerUp_prob) == 1)
			{
				row1[0] = '+';
			}
			else
				row1[0] = ' ';
					
			if ((rand() % object_generate_prob) == 1)
			{
				row2[0] = '#';
			}
			else if ((rand() % object_generate_prob) == 1)
			{
				row2[0] = '*';
			}
			else if ((rand() % AI_fire_prob) == 1 && AIPosition == 17)
			{
				row2[0] = '-';
			}
			else if ((rand() % powerUp_prob) == 1)
			{
				row2[0] = 0xFD;
			}
			else
				row2[0] = ' ';
			
			//set the last bit to '\0' to complete string
			if ((row1[16] != '\0' || row2[16] != '\0') && str_index >= 16)
			{
				row1[16] = '\0'; row2[16] = '\0';
				str_index = 16;
			}else str_index++;
			
			
			//arrayCpy(32);
		break;
	}
	
	return state;
}
#endif /* OBSTACLEGENERATOR_H_ */