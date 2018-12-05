/*******************************************************************************
 * @file		hMessageQueue.h
 * @brief		Message queue manager.
 * @author	llHoYall <hoya128@gmail.com>
 *******************************************************************************
 * @version	v1.0
 * @note
 *	- 2018.02.01	Created.
 ******************************************************************************/

#ifndef __HoYa_MESSAGE_QUEUE_H__
#define __HoYa_MESSAGE_QUEUE_H__

/* Definitions ---------------------------------------------------------------*/
#define MAX_MESSAGE				255

#define MESSAGE_START			0
#define MESSAGE_END				99

#define SEMAPHORE_START		100
#define SEMAPHORE_END			199

#define MUTEX_START				200
#define MUTEX_END					254

/* Structures ----------------------------------------------------------------*/
typedef struct _tMESSAGE_QUEUE {
	int	data;
	int	flag;
} tMESSAGE_QUEUE;

typedef struct _tMESSAGE_MANAGER {
	tMESSAGE_QUEUE	msg_pool[MAX_MESSAGE];

	void (*init)(void);
	int (*itc_put)(int, int);
	int (*itc_get)(int, int*);

	int (*sem_init)(int, int);
	int (*sem_p)(int);
	int (*sem_v)(int);

	int (*mutex_wait)(int);
	int (*mutex_release)(int);
} tMESSAGE_MANAGER;

/* API Prototypes ------------------------------------------------------------*/
void Message_Init(void);
int Message_Put(int, int);
int Message_Get(int, int*);

int Semaphore_Init(int, int);
int Semaphore_P(int);
int Semaphore_V(int);

int Mutex_Wait(int);
int Mutex_Release(int);

#endif
