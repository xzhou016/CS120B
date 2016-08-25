/*
 * FiringMech.h
 *
 * Created: 8/25/2016 4:35:53 AM
 *  Author: jakex
 */ 


#ifndef FIRINGMECH_H_
#define FIRINGMECH_H_

void shiftBullets(unsigned char shift)
{
	for (unsigned char i = shift ; i > 0; i--)
	{
		bulletRow[i - 1 ] = bulletRow[i];
	}
}

enum FiringMechSM {FM_start, FM_wait, FM_trigger, FM_release} FiringMechSM;

int FiringMech_Tick(int state) 
{
	switch(state)
	{
		case FM_start:
			state = FM_wait;
		break;
		
		case FM_wait:
			if (keypad_value == 'd')
			{
				state = FM_trigger;
			}
		break;
		
		case FM_trigger:
			state = FM_release;
		break;
		
		case FM_release:
			if (keypad_value != 'd')
			{
				state = FM_wait;
			}
		break;
		
		default:
			state = FM_start;
		break;
	}
	
	switch(state)
	{
		case FM_start: break;
		
		case FM_wait: 
			bulletRow[15] = 0;
			shiftBullets(str_index);
		break;
		
		case FM_trigger:
			bulletRow[15] = '-';
			//bullet = 1;
			//QueueEnqueue(bulletQ, 1);
		break;
		
		case FM_release:
			//bullet = 0;
		break;
		
		default: break;
	}
}


#endif /* FIRINGMECH_H_ */