/*
 * SCH.c
 *
 *  Created on: Nov 1, 2021
 *      Author: ADMIN
 */
#include "SCH.h"


static int size = 0;
static int Delaytrack;

void SCH_Init(void)
{
	unsigned char i ;
	for ( i = 0; i < SCH_MAX_TASKS; i ++)
	{
		SCH_Delete_Task(i) ;
	}
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
}


void SCH_Update( void )
{
	// Update with O1
	if (SCH_tasks_G[0].pTask)
	{
		if ( SCH_tasks_G[0].Delay == 0)
		{
			SCH_tasks_G[ 0 ] .RunMe += 1;
		}
		else
		{
			SCH_tasks_G[ 0 ].Delay -= 1;
		}
	}
}


unsigned char SCH_Add_Task( void (* pFunction) () , unsigned int DELAY, unsigned int PERIOD)
{
	int Index = 0;
		if(size == 0)
		{
			// If we ’ re here , there i s a space in the task array
				SCH_tasks_G[ Index ] . pTask = pFunction ;
				SCH_tasks_G[ Index ] . Delay = DELAY;
				SCH_tasks_G[ Index ] . Period = PERIOD;
				SCH_tasks_G[ Index ] .RunMe = 0;
				// return position of task ( to allow l at e r deletion )
				size++;
				Delaytrack = SCH_tasks_G[0].Delay;
				return Index;
		}
		while(DELAY > SCH_tasks_G[Index].Delay && Index < size && DELAY >= 0)
		{
	                DELAY -= SCH_tasks_G[Index].Delay;
			Index++;
		}
		if(DELAY < 0) DELAY = 0;
		for(int i = size; i > Index;i--)
		{
			SCH_tasks_G[i].pTask = SCH_tasks_G[i-1].pTask;
			SCH_tasks_G[i].Delay=SCH_tasks_G[i-1].Delay;
			SCH_tasks_G[i].Period=SCH_tasks_G[i-1].Period;
			SCH_tasks_G[i].RunMe=SCH_tasks_G[i-1].RunMe;
		}
		// If we ’ re here , there i s a space in the task array
		SCH_tasks_G[Index] . pTask = pFunction ;
		SCH_tasks_G[Index] . Delay = DELAY;
		SCH_tasks_G[Index ] . Period = PERIOD;
		SCH_tasks_G[ Index ] .RunMe = 0;
		size++;
		for(int j = Index; j < size-1;j++)
		{
			SCH_tasks_G[j+1].Delay -= DELAY;
		}
		// return position of task ( to allow l at e r deletion )
		return Index ;
}

void SCH_Dispatch_Tasks( void )
{
	int Index= 0;
	    if(SCH_tasks_G[0].RunMe > 0)
		{
		    (* SCH_tasks_G[ Index ] . pTask) () ;
		    SCH_tasks_G[0].RunMe -= 1;
		    sTask temp;
		    temp.pTask = SCH_tasks_G[0].pTask;
		    temp.Period = SCH_tasks_G[0].Period;
		    temp.Delay = SCH_tasks_G[0].Period;
		    temp.RunMe = SCH_tasks_G[0].RunMe;
		    for(int i = 0; i < size-1;i++)
		    {
		        SCH_tasks_G[i].pTask = SCH_tasks_G[i+1].pTask;
			SCH_tasks_G[i].Delay=SCH_tasks_G[i+1].Delay;
			SCH_tasks_G[i].Period=SCH_tasks_G[i+1].Period;
			SCH_tasks_G[i].RunMe=SCH_tasks_G[i+1].RunMe;
		    }
	            size--;
		    SCH_Add_Task(temp.pTask,temp.Delay, temp.Period);
		}
	// The scheduler enters idle mode at thi s point
	SCH_Go_To_Sleep() ;
}


void SCH_Delete_Task( const uint32_t TASK_INDEX)
{
	SCH_tasks_G[TASK_INDEX ] . pTask = 0x0000 ;
	SCH_tasks_G[TASK_INDEX ] . Delay = 0;
	SCH_tasks_G[TASK_INDEX ] . Period = 0;
	SCH_tasks_G[TASK_INDEX ] .RunMe = 0;
}

void SCH_Go_To_Sleep () {
//todo : Optional
}
