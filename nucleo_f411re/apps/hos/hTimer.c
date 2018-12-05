/*******************************************************************************
 * @file		hTimer.c
 * @brief		Timer utilities.
 * @author	llHoYall <hoya128@gmail.com>
 *******************************************************************************
 * @version	v1.0
 * @note
 *	- 2018.02.02	Created.
 ******************************************************************************/

/* Include Headers -----------------------------------------------------------*/
#include "hKernel.h"

/* Global Variables ----------------------------------------------------------*/
extern tTASK_BLOCK*	cur_task;

unsigned int hos_tick;

/* APIs ----------------------------------------------------------------------*/
int sleep(int sec) {
	while (1) {
		if (cur_task->end_tick == 0) {
			cur_task->end_tick = hos_tick + sec;
		}
		else if (cur_task->end_tick <= hos_tick) {
			cur_task->end_tick = 0;
			return 0;
		}
		else {
			Scheduler_Run();
		}
	}
	return 0;
}
