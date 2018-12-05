/*******************************************************************************
 * @file		hTask.h
 * @brief		Task manager.
 * @author	llHoYall <hoya128@gmail.com>
 *******************************************************************************
 * @version	v1.0
 * @note
 *	- 2018.01.24	Created.
 ******************************************************************************/

#ifndef __HOYA_TASK_H__
#define __HOYA_TASK_H__

/* Include Headers -----------------------------------------------------------*/
// Standard
#include <stdint.h>

/* Definitions ---------------------------------------------------------------*/
#define MAX_TASK_BLOCK	10
#define CONTEXT_SIZE		13

/* Structures ----------------------------------------------------------------*/
typedef struct _tTASK_BLOCK {
	uint32_t	context_spsr;
	uint32_t	context[CONTEXT_SIZE];
	uint32_t	context_sp;
	uint32_t	context_lr;
	uint32_t	context_pc;
	uint32_t	end_tick;
} tTASK_BLOCK;

typedef struct _tTASK_MANAGER {
	tTASK_BLOCK	task_pool[MAX_TASK_BLOCK];

	int max_task_id;

	void (*init)(void);;
	int (*create)(void(*pfnStart)(void));
} tTASK_MANAGER;

/* API Prototypes ------------------------------------------------------------*/
void Task_Init(void);
int Task_Create(void(*pfnStart)(void));
void UserTask_Create(void);

#endif
