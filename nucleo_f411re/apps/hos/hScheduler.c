/*******************************************************************************
 * @file		hScheduler.c
 * @brief		Scheduler of HoYa's os.
 * @author	llHoYall <hoya128@gmail.com>
 *******************************************************************************
 * @version	v1.0
 * @note
 *	- 2018.01.30	Created.
 ******************************************************************************/

/* Include Headers -----------------------------------------------------------*/
// Standard
#include <stdio.h>
// System
#include "hKernel.h"

/* Private Variables ---------------------------------------------------------*/
tTASK_BLOCK*	cur_task;
static tTASK_BLOCK*	next_task;
static tTASK_BLOCK	temp_task;
static int cur_index;

/* APIs ----------------------------------------------------------------------*/
int Scheduler_Init(void) {
	if (task_mng.max_task_id < 0) {
		return -1;
	}

	cur_task = &temp_task;
	next_task = &task_mng.task_pool[0];
	cur_index = -1;

	return 0;
}

void Scheduler_Run(void) {
	cur_task++;
	cur_index %= (task_mng.max_task_id + 1);
	next_task = &task_mng.task_pool[cur_index];
	cur_task = next_task;
}
