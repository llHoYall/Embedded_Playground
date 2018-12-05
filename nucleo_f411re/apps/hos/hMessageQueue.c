/*******************************************************************************
 * @file		hMessageQueue.c
 * @brief		Message queue manager.
 * @author	llHoYall <hoya128@gmail.com>
 *******************************************************************************
 * @version	v1.0
 * @note
 *	- 2018.02.01	Created.
 ******************************************************************************/

/* Include Headers -----------------------------------------------------------*/
#include "hKernel.h"

/* Global Variables ----------------------------------------------------------*/
extern tTASK_BLOCK*	cur_task;

tMESSAGE_MANAGER	msg_mng;

/* APIs ----------------------------------------------------------------------*/
void Message_Init(void) {
	for (int i = 0; i < MAX_MESSAGE; i++) {
		msg_mng.msg_pool[i].data = 0;
		msg_mng.msg_pool[i].flag = 0;
	}

	msg_mng.init = Message_Init;
	msg_mng.itc_put = Message_Put;
	msg_mng.itc_get = Message_Get;

	msg_mng.sem_init = Semaphore_Init;
	msg_mng.sem_p = Semaphore_P;
	msg_mng.sem_v = Semaphore_V;

	msg_mng.mutex_wait = Mutex_Wait;
	msg_mng.mutex_release = Mutex_Release;
}

int Message_Put(int idx, int data) {
	if (idx >= MAX_MESSAGE || idx < 0) {
		return -1;
	}

	msg_mng.msg_pool[idx].data = data;
	msg_mng.msg_pool[idx].flag = 1;

	return idx;
}

int Message_Get(int idx, int* data) {
	if (idx >= MAX_MESSAGE || idx < 0) {
		return -1;
	}

	if (msg_mng.msg_pool[idx].flag == 0) {
		return -2;
	}

	*data = msg_mng.msg_pool[idx].data;
	msg_mng.msg_pool[idx].data = 0;
	msg_mng.msg_pool[idx].flag = 0;

	return 0;
}

int Semaphore_Init(int idx, int s) {
	idx += SEMAPHORE_START;
	if (idx > SEMAPHORE_END || idx < SEMAPHORE_START) {
		return -1;
	}

	msg_mng.msg_pool[idx].flag = s;
	return 0;
}

int Semaphore_P(int idx) {
	idx += SEMAPHORE_START;
	if (idx > SEMAPHORE_END || idx < SEMAPHORE_START) {
		return -1;
	}
	if (msg_mng.msg_pool[idx].flag <= 0) {
		return -2;
	}

	--msg_mng.msg_pool[idx].flag;
	return 0;
}

int Semaphore_V(int idx) {
	idx += SEMAPHORE_START;
	if (idx > SEMAPHORE_END || idx < SEMAPHORE_START) {
		return -1;
	}

	++msg_mng.msg_pool[idx].flag;
	return 0;
}

int Mutex_Wait(int idx) {
	idx += MUTEX_START;
	if (idx > MUTEX_END || idx < MUTEX_END) {
		return -1;
	}

	if (msg_mng.msg_pool[idx].flag == 0) {
		msg_mng.msg_pool[idx].flag = 1;
		msg_mng.msg_pool[idx].data = (unsigned int)cur_task;
	}
	else {
		return -2;
	}
	return 0;
}

int Mutex_Release(int idx) {
	idx += MUTEX_START;
	if (idx > MUTEX_END || idx < MUTEX_END) {
		return -1;
	}
	if (msg_mng.msg_pool[idx].data != (unsigned int)cur_task) {
		return -2;
	}

	msg_mng.msg_pool[idx].flag = 0;
	msg_mng.msg_pool[idx].data = 0;
	return 0;
}
