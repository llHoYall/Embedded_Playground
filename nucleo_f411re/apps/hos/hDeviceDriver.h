/*******************************************************************************
 * @file		hDeviceDriver.h
 * @brief		Device driver.
 * @author	llHoYall <hoya128@gmail.com>
 *******************************************************************************
 * @version	v1.0
 * @note
 *	- 2018.02.08	Created.
 ******************************************************************************/

#ifndef __HoYa_DEVICE_DRIVER_H__
#define __HoYa_DEVICE_DRIVER_H__

/* Include Headers -----------------------------------------------------------*/
// Standard Header
#include <stdint.h>

/* Definitions ---------------------------------------------------------------*/
#define DRIVER_LIMIT				10
#define O_RDONLY						0
#define O_WRONLY						1
#define O_RDWR							2

/* Structures ----------------------------------------------------------------*/
typedef struct _tFOPS {
	int (*open)(int drvnum, int mode);
	int (*read)(int drvnum, void* buf, int size);
	int (*write)(int drvnum, void* buf, int size);
	int (*close)(int drvnum);
} tFOPS;

typedef struct _tDRIVER {
	tFOPS*	fops;
	int	usecount;
	const char* drvnum;
} tDRIVER;

typedef struct _tDRIVER_MANAGER {
	tDRIVER drv_pool[DRIVER_LIMIT];

	void (*init)(void);
	uint32_t (*reg)(int, const char* tFOPS*);
} tDRIVER_MANAGER;

/* API Prototypes ------------------------------------------------------------*/
void Drv_Init(void);
int Drv_Register(int, const char* tFOPS*);

#endif
