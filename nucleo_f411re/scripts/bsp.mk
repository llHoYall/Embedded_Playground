################################################################################
#	@brief		Makefile for BSP.
#	@author		llHoYall <HoYa128@gmail.com>
#	@version	v1.0
#	@history
#		- 2018.12.04	Created.
################################################################################

# Sources
BSP_SRCS	:= $(wildcard $(PATH_BSP)/$(BOARD)/*.c)

# Objects
BSP_OBJS	:= $(patsubst %.c,$(PATH_OBJ)/$(BOARD)/%.o,$(notdir $(BSP_SRCS)))

# Includes
BSP_INCS	:= -I$(PATH_BSP)/$(BOARD)

# Dependencies
BSP_DEPS	:= $(patsubst %.c,$(PATH_DEP)/$(BOARD)/%.d,$(notdir $(BSP_SRCS)))

# Definitions
BSP_DEFS	:= -DUSE_STM32F4XX_NUCLEO
