/*******************************************************************************
 * @file		hMemory.h
 * @brief		Memory manager.
 * @author	llHoYall <hoya128@gmail.com>
 *******************************************************************************
 * @version	v1.0
 * @note
 *	- 2018.01.21	Created.
 ******************************************************************************/

#ifndef __HoYa_MEMORY_H__
#define __HoYa_MEMORY_H__

/* Include Headers -----------------------------------------------------------*/
// Standard Header
#include <stdint.h>

/* Definitions ---------------------------------------------------------------*/
#define MAX_MEMORY_BLOCK				10
#define START_USER_STACK_ADDR		0x20001000
#define USER_STACK_SIZE					0x0400
#define START_HEAP_ADDR					0x2000b800
#define END_HEAP_ADDR						0x20018000

/* Structures ----------------------------------------------------------------*/
typedef struct _tMEMORY_BLOCK {
	uint32_t	start_addr;
	uint32_t	end_addr;
	int32_t		is_used;
} tMEMORY_BLOCK;

typedef struct _tHEAP_HEADER {
	int	used;
	int	size;
} tHEAP_HEADER;

typedef struct _tMEMORY_MANAGER {
	tMEMORY_BLOCK mem_pool[MAX_MEMORY_BLOCK];

	uint32_t	heap_start;
	uint32_t	heap_end;

	void (*init)(void);
	uint32_t (*alloc)(void);

	void* (*malloc)(int);
	int (*free)(void*);
} tMEMORY_MANAGER;

/* API Prototypes ------------------------------------------------------------*/
void Mem_Init(void);

#endif
