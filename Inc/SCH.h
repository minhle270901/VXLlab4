/*
 * SCH.h
 *
 *  Created on: Nov 1, 2021
 *      Author: ADMIN
 */

#ifndef INC_SCH_H_
#define INC_SCH_H_
#include "main.h"
#include <stdlib.h>
#include "taskarray.h"
#include "timer.h"

// MUST BE ADJUSTED FOR EACH NEW PROJECT
#define SCH_MAX_TASKS 40
#define NO_TASK_ID 0
sTask SCH_tasks_G[SCH_MAX_TASKS] ;

void SCH_Init ( void );
unsigned char SCH_Add_Task( void (* pFunction) () , unsigned int DELAY, unsigned int PERIOD);
void SCH_Dispatch_Tasks( void );
void SCH_Update( void );
void SCH_Go_To_Sleep (void);
void SCH_Delete_Task( const uint32_t TASK_INDEX);


#endif /* INC_SCH_H_ */
