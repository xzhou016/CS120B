/*
 * ObstacleGenerator.h
 *
 * Created: 8/18/2016 12:14:01 AM
 *  Author: jakex
 */ 


#ifndef OBSTACLEGENERATOR_H_
#define OBSTACLEGENERATOR_H_

unsigned char str_index = 1;

void arrayShift(unsigned char shift)
{
	unsigned char temp;
	for (unsigned char i = shift ; i > 0; i--)
	{
		row1[i] = row1[i - 1];
		row2[i] = row2[i - 1 ];
	}
}

enum ObstacleGeneratorSM {OGSM_start, OGSM_generate} ObstacleGeneratorSM;
int ObstacleGeneratorSM_Tick(int state)
{
	switch(state) //state transition
	{
		case OGSM_start: 
			state = OGSM_generate;
			
		break;
		
		case OGSM_generate: break;
		
		default: 
			state = OGSM_start;
		break;
	}
	
	switch(state) //state actions
	{
		case OGSM_start: 
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
			else
				row2[0] = ' ';
			
			//memcpy(display_string, row1, str_index );
			//memcpy(display_string, row2, str_index + 1);	
			
			//set the last bit to '\0' to complete string
			if ((row1[15] != '\0' || row2[15] != '\0') && str_index > 16)
			{
				row1[15] = '\0'; row2[15] = '\0';
				str_index = 15;
			}else str_index++;
		break;
	}
	
	return state;
}
#endif /* OBSTACLEGENERATOR_H_ */