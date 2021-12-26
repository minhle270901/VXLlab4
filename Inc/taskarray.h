/*
 * taskarray.h
 *
 *  Created on: Nov 2, 2021
 *      Author: ADMIN
 */

#ifndef INC_TASKARRAY_H_
#define INC_TASKARRAY_H_

typedef struct {
	// Pointer to the task (must be a ’ void ( void ) ’ function )
	void ( * pTask) ( void ) ;
	// Delay ( ti ck s ) until the function will ( next ) be run
	uint32_t Delay ;
	// Interval ( ti ck s ) between subsequent runs .
	uint32_t Period ;
	// Incremented ( by scheduler ) when task is due to execute
	uint8_t RunMe;
	// This i s a hint to solve the question below .
	uint32_t TaskID ;
} sTask ;


#endif /* INC_TASKARRAY_H_ */
