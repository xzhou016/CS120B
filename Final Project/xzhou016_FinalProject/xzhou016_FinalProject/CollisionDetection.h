/*
 * CollisionDetection.h
 *
 * Created: 8/22/2016 6:42:39 PM
 *  Author: jakex
 */ 


#ifndef COLLISIONDETECTION_H_
#define COLLISIONDETECTION_H_

enum CollisionSM {C_start, C_detect} CollisionSM;

int Collision_Tick(int state) 
{
	switch(state)
	{
		case C_start:
			isHit					= 0;		
			state = C_detect;
		break;
		
		case C_detect:
			state = C_detect;
		break;
		
		default: 
			state = C_start;
		break;
		
	}
	
	switch(state)
	{
		case C_start:
		break;
			
		case C_detect:
			if (playerPosition == 16 && (row1[15] != 32 && row1[15] != 0))
			{
				isHit = 1;
				playerIcon = 'X';
			} 
			else if (playerPosition == 32 && (row2[15] != 32 && row2[15] != 0))
			{
				isHit = 1;
				playerIcon = 'X';
			}

			break;	
			
		default:break;
	}
	
	return state;
}


#endif /* COLLISIONDETECTION_H_ */