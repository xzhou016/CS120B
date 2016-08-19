/* 
* Name: Jia Jun Yu
* Email: jyu052@ucr.edu
* Name: Xiao Zhou
* Email: xzhou016@ucr.edu
* Lab Section: 21
* Assignment: Lab#8 Exercise#4
*
* I acknowledge all content contained herein, excluding 
* template or example code, is my own original work.
*/

#include <avr/io.h>

void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: setting this bit enables analog-to-digital conversion.
	// ADSC: setting this bit starts the first conversion.
	// ADATE: setting this bit enables auto-triggering. Since we are
	//        in Free Running Mode, a new conversion will trigger whenever
	//        the previous conversion completes.
}

int main(void)
{
	DDRA = 0x00;
	DDRB = 0xFF; PORTB = 0x00;
	
	ADC_init();
	unsigned char tempB = 0x00;
	
    while (1) 
    {
		if(ADC <= 15)
		{
			tempB = 0x00;
		}
		else if(ADC > 15 && ADC < 17)
		{
			tempB = 0x01;
		}
		else if(ADC >= 17 && ADC < 19)
		{
			tempB = 0x03;
		}
		else if(ADC >= 19 && ADC < 21)
		{
			tempB = 0x07;
		}
		else if(ADC >= 21 && ADC < 23)
		{
			tempB = 0x0F;
		}
		else if(ADC >= 23 && ADC < 25)
		{
			tempB = 0x1F;
		}
		else if(ADC >= 25 && ADC < 27)
		{
			tempB = 0x3F;
		}
		else if(ADC >= 27 && ADC < 29)
		{
			tempB = 0x7F;
		}
		else if(ADC >= 29)
		{
			tempB = 0xFF;
		}
		PORTB = tempB;
    }
}