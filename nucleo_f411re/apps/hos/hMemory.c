/*******************************************************************************
 * @file		hMemory.c
 * @brief		Memory manager.
 * @author	llHoYall <hoya128@gmail.com>
 *******************************************************************************
 * @version	v1.0
 * @note
 *	- 2018.01.21	Created.
 ******************************************************************************/

/* Include Headers -----------------------------------------------------------*/
//	System
#include "hKernel.h"

/* Global Variables ----------------------------------------------------------*/
tMEMORY_MANAGER mem_mng;

/* Private Function Prototypes -----------------------------------------------*/
static uint32_t Mem_Alloc(void);
static void* Heap_Malloc(int size);
static int Heap_Free(void* addr);

/* APIs ----------------------------------------------------------------------*/
void Mem_Init(void) {
	uint32_t	addr = START_USER_STACK_ADDR;
	for (int i = 0; i < MAX_MEMORY_BLOCK; i++) {
		mem_mng.mem_pool[i].start_addr = addr;
		mem_mng.mem_pool[i].end_addr = addr + USER_STACK_SIZE - 4;
		mem_mng.mem_pool[i].is_used = 0;
		addr += USER_STACK_SIZE;
	}
	mem_mng.heap_start = START_HEAP_ADDR;
	mem_mng.heap_end = mem_mng.heap_start;

	mem_mng.init = Mem_Init;
	mem_mng.alloc = Mem_Alloc;

	mem_mng.malloc = Heap_Malloc;
	mem_mng.free = Heap_Free;
}

/* Private Functions ---------------------------------------------------------*/
static uint32_t Mem_Alloc(void) {
	for (int i = 0; i < MAX_MEMORY_BLOCK; i++) {
		if (mem_mng.mem_pool[i].is_used == 0) {
			mem_mng.mem_pool[i].is_used = 1;
			return mem_mng.mem_pool[i].end_addr;
		}
	}
	return 0;
}

static void* Heap_Malloc(int size) {
	int req_size = size + sizeof(tHEAP_HEADER);
	uint32_t cur_pos = mem_mng.heap_start;
	uint32_t ret_addr = 0;
	tHEAP_HEADER* header;

	while (cur_pos != mem_mng.heap_end) {
		header = (tHEAP_HEADER*)cur_pos;
		if (!header->used) {
			if (header->size >= req_size) {
				header->used = 1;
				ret_addr = cur_pos;
				break;
			}
		}
		cur_pos += header->size;
	}

	if (!ret_addr) {
		ret_addr = mem_mng.heap_end;
		mem_mng.heap_end += req_size;
		if (mem_mng.heap_end > END_HEAP_ADDR) {
			return (void*)0;
		}
		header = (tHEAP_HEADER*)ret_addr;
		header->used = 1;
		header->size = req_size;
	}
	ret_addr += sizeof(tHEAP_HEADER);
	return (void*)ret_addr;
}

static int Heap_Free(void* addr) {
	uint32_t addr_header = (uint32_t)addr - sizeof(tHEAP_HEADER);
	tHEAP_HEADER* header;
	header = (tHEAP_HEADER*)addr_header;
	if (header->used != 1) {
		return -1;
	}
	header->used = 0;
	return 0;
}
