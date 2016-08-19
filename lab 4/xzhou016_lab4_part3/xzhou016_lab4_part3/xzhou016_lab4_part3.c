/*	xzhou016_lab4_part3.c -
 *	Name & E-mail:  - Xiao Zhou, xzhou016@ucr.edu
 *	CS Login: xzhou016
 *	Partner(s) Name & E-mail:  - Jia Jun Yu, jyu052@ucr.edu
 *	Lab Section: 21
 *	Assignment: Lab #4  Exercise #3
 *	Exercise Description:
 *	
 *	
 *	I acknowledge all content contained herein, excluding template or example 
 *	code, is my own original work.
 */ 
#include <avr/io.h>
enum Festive_State {SM_START, SM_INIT, SM_WAIT, SM_RELEASE,
					 SM_STAGE1, SM_STAGE2, 
					 SM_STAGE3, SM_STAGE4, SM_STAGE5,
					 SM_STAGE6, SM_STAGE7 } Festive_State;
					 
unsigned char setPortC = 0x00;

void TickCount()
{
	unsigned char setPinA = ~PINA & 0x01; //using temp to read from PINA and mask it
	
	//changing states
	switch (Festive_State)
	{
		case SM_START:
			Festive_State = SM_INIT;
			break;
		case SM_INIT:
			if ( setPinA == 0x00)
			{
				//remain in init
			} else if (setPinA == 0x01)
			{
				Festive_State = SM_WAIT;
			}
			
			break;
		case SM_WAIT :
			if (setPinA == 0x01 && setPortC == 0x00 )
			{
				Festive_State = SM_STAGE1;
			} else if (setPinA == 0x01 && setPortC == 0x07)
			{
				Festive_State = SM_STAGE2;
			}else if (setPinA == 0x01 && setPortC == 0x0E)
			{
				Festive_State = SM_STAGE3;
			} else if (setPinA == 0x01 && setPortC == 0x1C)
			{
				Festive_State = SM_STAGE4;
			} else if (setPinA == 0x01 && setPortC == 0x38)
			{
				Festive_State = SM_STAGE5;
			} else if (setPinA == 0x01 && setPortC == 0x70)
			{
				Festive_State = SM_STAGE6;
			} else if (setPinA == 0x01 && setPortC == 0x61)
			{
				Festive_State = SM_STAGE7;
			} else if (setPinA == 0x01 && setPortC == 0x43)
			{
				Festive_State = SM_INIT;
			}else
			{
				// remain in wait
			}
			break;
		case SM_RELEASE :
			if (setPinA == 0x01)
			{
				Festive_State = SM_RELEASE;
			} 
			else if (setPinA == 0x00)
			{
				Festive_State = SM_WAIT;
			}
			
			break;
		default:
			Festive_State = SM_START;
	}
	
	//set lighting for stages
	switch (Festive_State)
	{
		case SM_INIT :
			setPortC = 0x00;
			Festive_State = SM_RELEASE ;
			break;
		case SM_STAGE1 :
			setPortC = 0x07;
			Festive_State = SM_RELEASE;
			break;
		case SM_STAGE2 :
			setPortC = 0x0E;
			Festive_State = SM_RELEASE;
			break;
		case SM_STAGE3 :
			setPortC = 0x1C;
			Festive_State = SM_RELEASE;
			break;
		case SM_STAGE4 :
			setPortC = 0x38;
			Festive_State = SM_RELEASE;
			break;
		case SM_STAGE5 : 
			setPortC = 0x70;
			Festive_State = SM_RELEASE;
			break;
		case SM_STAGE6 :
			setPortC = 0x61;
			Festive_State = SM_RELEASE;
			break;
		case SM_STAGE7 : 
			setPortC = 0x43;
			Festive_State = SM_RELEASE;
			break;
		default:
			break;
		
	}
	
	PORTC = setPortC;
	
}



int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	
	Festive_State = SM_START; //set state
    while (1) 
    {
		TickCount();
    }
}

