/*******************************************************************************
 * @file		hKernel.c
 * @brief		Kernel of HoYa's os.
 * @author	llHoYall <hoya128@gmail.com>
 *******************************************************************************
 * @version	v1.0
 * @note
 *	- 2018.01.25	Created.
 ******************************************************************************/

/* Include Headers -----------------------------------------------------------*/
// Standard Header
#include <stdio.h>
// System Header
#include "hKernel.h"

/* APIs ----------------------------------------------------------------------*/
int Kernel_Init(void) {
	hos_tick = 0;

	Mem_Init();
	Task_Init();
	Message_Init();

	UserTask_Create();
	if (Scheduler_Init() < 0) {
		printf("Error: Scheduler_Init()\r\n");
		return -1;
	}
	return 0;
}
