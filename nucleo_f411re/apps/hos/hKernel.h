/*******************************************************************************
 * @file		hKernel.h
 * @brief		Kernel of HoYa's os.
 * @author	llHoYall <hoya128@gmail.com>
 *******************************************************************************
 * @version	v1.0
 * @note
 *	- 2018.01.25	Created.
 ******************************************************************************/

#ifndef __HoYa_KERNEL_H__
#define __HoYa_KERNEL_H__

/* Include Headers -----------------------------------------------------------*/
// System Header
#include "hTimer.h"
#include "hMemory.h"
#include "hTask.h"
#include "hMessageQueue.h"
#include "hScheduler.h"

/* Global Variables ----------------------------------------------------------*/
extern tMEMORY_MANAGER	mem_mng;
extern tTASK_MANAGER		task_mng;

/* API Prototypes ------------------------------------------------------------*/
int Kernel_Init(void);

#endif
