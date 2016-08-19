/*
 * ObstacleGenerator.h
 *
 * Created: 8/15/2016 11:33:02 PM
 *  Author: jakex
 */ 


#ifndef OBSTACLEGENERATOR_H_
#define OBSTACLEGENERATOR_H_
#include <stdlib.h>
	
void ObstacleGenerator() 
{
	for (int i = 0; i < 32 ; i++)
	{
		if ((rand() % 6) == 1)
		{
			display_string[i] = '#';
		}
		else
			display_string[i] = ' ';
	}
	display_string[31] = '\0';
}



#endif /* OBSTACLEGENERATOR_H_ */