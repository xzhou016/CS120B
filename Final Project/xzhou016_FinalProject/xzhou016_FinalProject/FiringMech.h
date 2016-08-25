/*
 * FiringMech.h
 *
 * Created: 8/25/2016 4:35:53 AM
 *  Author: jakex
 */ 


#ifndef FIRINGMECH_H_
#define FIRINGMECH_H_
enum FiringMechSM {FM_start, FM_wait, FM_trigger, FM_release} FiringMechSM;

int FiringMech_Tick(int state) 
{
	switch(state)
	{
		case FM_start:
			state = FM_wait;
		break;
		
		case FM_wait:
			if (keypad_value == 'D')
			{
				state = FM_trigger;
			}
		break;
		
		case FM_trigger:
			state = FM_release;
		break;
		
		case FM_release:
			if (keypad_value != 'D')
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
			if (bulletPos > 0)
			{
				bulletPos--;
			}
		break;
		
		case FM_trigger:
			bullet = 1;
			
			bulletPos = playerPosition - 1;
			
		break;
		
		case FM_release:
		break;
		
		default: break;
	}
	
	return state;
}


#endif /* FIRINGMECH_H_ */