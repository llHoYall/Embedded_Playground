/*******************************************************************************
 * @file		utils/hDef.h
 * @brief		HoYa's definitions.
 * @author	llHoYall <hoya128@gmail.com>
 *******************************************************************************
 * @version	v1.0
 * @note
 *	- 2018.02.02	Created.
 ******************************************************************************/

#ifndef __HoYa_DEFINITIONS_H__
#define __HoYa_DEFINITIONS_H__

/* for Compiler --------------------------------------------------------------*/
#define UNUSED(x)		((void)(x))

#if defined (__GNUC__) && !defined (__CC_ARM)
	#ifndef __weak
		#define __weak		__attribute__((weak))
	#endif
#endif

#endif
