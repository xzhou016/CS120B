//external library
#include <avr/io.h>
#include <avr/interrupt.h>
#include "io.c"
#include "bit.h"
#include "timer.h"
#include "scheduler.h"
//#include "keypad.h"
#include "keypad_custom.h"
#include "queue.h"

//global variables
unsigned char keypad_value			= 0x00;
unsigned char row1[17]				= " ";
unsigned char row2[17]				= " ";
unsigned char bulletRow[15];
unsigned char object_generate_prob	= 20;
unsigned char beginGenerate			= 0;
unsigned char restart				= 0;
unsigned char playerPosition		= 16;
unsigned char isHit					= 0;
unsigned char playerIcon			= 0xDB;
unsigned char str_index				= 1;
<<<<<<< HEAD
unsigned char bullet				= 0;
Queue bulletQ;

//Tasks
static task task1, task2, task3, task4, task5;
task *tasks[]					= {&task1 , &task2, &task3, &task4, &task5};
=======
unsigned char playerScore[10];
//unsigned char playerScoreArr[2]; 
//Queue myQ;

//Tasks
static task	 task1, task2, task3, task4, task5;
task *tasks[] = {&task1 , &task2, &task3, &task4, &task5};
>>>>>>> refs/remotes/origin/LevelProgression

//state machines
#include "ObstacleGenerator.h"
//#include "KeypadReadSM.h"
#include "Display.h"
#include "Movement.h"
#include "CollisionDetection.h"
#include "LevelProgression.h"



int main(void)
{
	DDRB = 0xFF; PORTB = 0x00; // PORTB set to output, outputs init 0s
	DDRC = 0xF0; PORTC = 0x0F; // PC7..4 outputs init 0s, PC3..0 inputs init 1s
	DDRD = 0xFF; PORTD = 0x00;
	
	bulletQ = QueueInit(1);

	/**Set individual task period********************************/
	unsigned long int ObstacleGenerator_calc	= 500;
	unsigned long int Display_calc				= 500;
// 	unsigned long int Movement_calc				= 500;
// 	unsigned long int Collision_calc			= 500;
	unsigned long int Movement_calc				= 10;
	unsigned long int Collision_calc			= 100;
	unsigned long int LevelProgression_calc		= 1200;
	
		
	/**Set individual task properties********************************/
	
	//Calculating GCD
	unsigned long int tempGCD		= findGCD(ObstacleGenerator_calc, Display_calc);
					  tempGCD		= findGCD(tempGCD, Movement_calc);
					  tempGCD		= findGCD(tempGCD, Collision_calc);
					  tempGCD		= findGCD(tempGCD, LevelProgression_calc);
	unsigned long int GCD			= tempGCD;
	//Recalculate GCD periods for scheduler
	unsigned long int Tick1_Period	= ObstacleGenerator_calc/GCD,
					  Tick2_period	= Display_calc/GCD,
					  Tick3_period	= Movement_calc/GCD,
					  Tick4_period	= Collision_calc/GCD,
					  Tick5_period	= LevelProgression_calc/GCD;
	const unsigned short numTasks	= sizeof(tasks)/sizeof(task*);
	
	/****************************************************************/
	
	/**Set individual task properties**************/
	task1.state						= 0;
	task1.period					= Tick1_Period;
	task1.elapsedTime				= Tick1_Period;
	task1.TickFct					= &ObstacleGeneratorSM_Tick;
	
	// Task 2
	task2.state						= 0;//Task initial state.
	task2.period					= Tick2_period;//Task Period.
	task2.elapsedTime				= Tick2_period;//Task current elapsed time.
	task2.TickFct					= &DisplaySM_Tick;//Function pointer for the tick.
	
	//Task 3
	task3.state						= 0;//Task initial state.
	task3.period					= Tick3_period;//Task Period.
	task3.elapsedTime				= Tick3_period;//Task current elapsed time.
	task3.TickFct					= &Movement_Tick;//Function pointer for the tick.
	
	//Task 4
	task4.state						= 0;//Task initial state.
	task4.period					= Tick4_period;//Task Period.
	task4.elapsedTime				= Tick4_period;//Task current elapsed time.
	task4.TickFct					= &Collision_Tick;//Function pointer for the tick.
	
	//Task 5
	task5.state						= 0;//Task initial state.
	task5.period					= Tick5_period;//Task Period.
	task5.elapsedTime				= Tick5_period;//Task current elapsed time.
	task5.TickFct					= &LevelProgression_Tick;//Function pointer for the tick.

	/**********************************************/
	
	
	TimerSet(GCD);
	TimerOn();
	
	LCD_init();
	
	while(1) 
	{
		for(unsigned short i = 0; i < numTasks; i++)
		{
			//keypad_value = GetKeypadKey();
			if(tasks[i] -> elapsedTime == tasks[i]-> period)
			{
				
				tasks[i] -> state		= tasks[i] -> TickFct(tasks[i] -> state);
				tasks[i] -> elapsedTime = 0;
			}
			tasks[i] -> elapsedTime += 1;
		}
		while(!TimerFlag);
		TimerFlag = 0;
	}
	return 0;
}