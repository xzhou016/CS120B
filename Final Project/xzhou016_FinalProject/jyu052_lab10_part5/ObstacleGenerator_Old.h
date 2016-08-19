/*
 * ObstacleGenerator.h
 *
 * Created: 8/15/2016 11:33:02 PM
 *  Author: jakex
 */ 


#ifndef OBSTACLEGENERATOR_H_
#define OBSTACLEGENERATOR_H_
#include <stdlib.h>
	
void ObstacleGenerator(unsigned long size) 
{
	for (int i = 0; i < size ; i++)
	{
		if ((rand() % 6) == 1)
		{
			display_string[i] = '#';
			
		}
		else if ((rand() % 6) == 1)
		{
			display_string[i] = '*';
		}
		else
			display_string[i] = ' ';
		//QueueEnqueue(mQ, )
	}

	display_string[size - 1] = '\0';
}



#endif /* OBSTACLEGENERATOR_H_ */