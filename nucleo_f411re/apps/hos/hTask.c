/*******************************************************************************
 * @file		hTask.c
 * @brief		Task manager.
 * @author	llHoYall <hoya128@gmail.com>
 *******************************************************************************
 * @version	v1.0
 * @note
 *	- 2018.01.24	Created.
 ******************************************************************************/

/* Include Headers -----------------------------------------------------------*/
// Standard Header
#include <stdio.h>
#include <string.h>
// System Header
#include "hDef.h"
#include "hKernel.h"

/* Global Variables ----------------------------------------------------------*/
tTASK_MANAGER	task_mng;

/* Definitions ---------------------------------------------------------------*/
#define START_USER_CPSR		0x60000000

/* APIs ----------------------------------------------------------------------*/
void Task_Init(void) {
	for (int i = 0; i < MAX_TASK_BLOCK; i++) {
		task_mng.task_pool[i].context_spsr = 0x00;
		memset(task_mng.task_pool[i].context, 0, sizeof(uint32_t) * CONTEXT_SIZE);
		task_mng.task_pool[i].context_sp = 0x00;
		task_mng.task_pool[i].context_lr = 0x00;
		task_mng.task_pool[i].context_pc = 0x00;
		task_mng.task_pool[i].end_tick = 0;
	}
	task_mng.max_task_id = -1;

	task_mng.init = Task_Init;
	task_mng.create = Task_Create;
}

int Task_Create(void(*pfnStart)(void)) {
	int task_idx = 0;
	uint32_t stack_top = 0;

	task_mng.max_task_id++;
	task_idx = task_mng.max_task_id;

	if (task_idx >= MAX_TASK_BLOCK) {
		return -1;
	}

	stack_top = mem_mng.alloc();
	if (stack_top == 0) {
		return -2;
	}

	task_mng.task_pool[task_idx].context_spsr = START_USER_CPSR;
	task_mng.task_pool[task_idx].context_sp = stack_top;
	task_mng.task_pool[task_idx].context_pc = (uint32_t)pfnStart;

	return task_idx;
}

__weak void UserTask_Create(void) {
	puts("Must create task\r\n");
}
