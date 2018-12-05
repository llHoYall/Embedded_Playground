################################################################################
#	@file			freertos.mk
#	@brief		Makefile for FreeRTOS.
#	@author		llHoYall <HoYa128@gmail.com>
################################################################################
#	@version	v1.0
#	@note
#		- 2018.01.30	Created.
################################################################################

FREERTOS_SRCS	+= $(wildcard middlewares/freertos/*.c)
FREERTOS_INCS	 = -Imiddlewares/freertos
