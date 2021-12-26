/*
 * timer.c
 *
 *  Created on: Nov 1, 2021
 *      Author: ADMIN
 */
#include "timer.h"

void HAL_TIM_PeriodElapsedCallback ( TIM_HandleTypeDef * htim )
{
	HAL_ResumeTick();
	SCH_Update() ;
}
