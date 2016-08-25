/*
 * CollisionDetection.h
 *
 * Created: 8/22/2016 6:42:39 PM
 *  Author: jakex
 */ 


#ifndef COLLISIONDETECTION_H_
#define COLLISIONDETECTION_H_

void destroyObj()
{
	for (unsigned i = 0; i < 16; i++)
	{
		if (playerPosition == 16 )
		{
			if (bulletRow[i] == '-' && (row1[i] == '*' || row1[i] == '#' ))
			{
				row1[i] = ' ';
			}
		}else if (playerPosition == 32)
		{
			if (bulletRow[i] == '-' && (row2[i] == '*' || row2[i] == '#' ))
			{
				row2[i] = ' ';
			}
		}
	}
}

enum CollisionSM {C_start, C_detect} CollisionSM;

int Collision_Tick(int state) 
{
	switch(state)
	{
		case C_start:
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
			isHit = 0;
		break;
			
		case C_detect:
			
			if (bullet == 1)
			{
				if (bulletPos < 16 && (row1[bulletPos - 1] == '*' || row1[bulletPos -1] == '#'))
				{
					row1[bulletPos - 1] = ' ';
					bullet = 0;
				}else if(bulletPos < 32 && (row2[bulletPos - 17 ] == '*' || row2[bulletPos - 17] == '#') )
				{
					row2[bulletPos - 17] = 32;
					bullet = 0;
				}
			}
			if (playerPosition == 16 && (row1[15] != 32 && row1[15] != 0))
			{
				isHit	= 1;
			} 
			else if (playerPosition == 32 && (row2[15] != 32 && row2[15] != 0))
			{
				isHit	= 1;
			}

			break;	
			
		default:break;
	}
	
	return state;
}


#endif /* COLLISIONDETECTION_H_ */