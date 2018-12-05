################################################################################
#	@brief		Makefile for stm32f411re platform.
#	@author		llHoYall <HoYa128@gmail.com>
#	@version	v1.0
#	@history
#		- 2018.12.05	Created.
################################################################################

# Startup code
STARTUP				:= ./drivers/cmsis/$(MCU)/startup/startup_$(MCU).s

# Sources
PLATFORM_SRCS	:= $(wildcard ./drivers/bsp/$(BOARD)/*.c)
PLATFORM_SRCS	+= $(wildcard ./drivers/cmsis/$(MCU)/*.c)
PLATFORM_SRCS	+= $(wildcard ./drivers/stm32f4xx_hal/**/*.c)

# Includes
PLATFORM_INCS	:= -I./drivers/bsp/$(BOARD)
PLATFORM_INCS	+= -I./drivers/cmsis/inc
PLATFORM_INCS	+= -I./drivers/cmsis/$(MCU)
PLATFORM_INCS	+= -I./drivers/stm32f4xx_hal
PLATFORM_INCS	+= -I./drivers/stm32f4xx_hal/Legacy

# Definitions
PLATFORM_DEFS	:= -DSTM32F411xE
PLATFORM_DEFS	+= -DUSE_HAL_DRIVER

# Linker Script
LD_SCRIPT			:= ./drivers/cmsis/$(MCU)/linker/STM32F411RETx_FLASH.ld

# Objects
PLATFORM_OBJS	:= $(patsubst %.c,$(PATH_OBJ)/$(BOARD)/%.o,$(notdir $(STARTUP)))
PLATFORM_OBJS	:= $(patsubst %.c,$(PATH_OBJ)/$(BOARD)/%.o,$(notdir $(PLATFORM_SRCS)))

# Dependencies
PLATFORM_DEPS	:= $(patsubst %.c,$(PATH_DEP)/$(MCU)/%.d,$(notdir $(PLATFORM_SRCS)))
