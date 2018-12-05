################################################################################
# @brief		Makefile for arm-none-eabi- tools
# @author		HoYa <hoya128@nextchip.com>
# @version	v1.0
# @history
#		- 2018.12.04	Created.
################################################################################

# Compile Tools
ARM_GCC	:= arm-none-eabi-
AS			:= $(ARM_GCC)gcc
CC			:= $(ARM_GCC)gcc
LD			:= $(ARM_GCC)gcc
OBJCOPY	:= $(ARM_GCC)objcopy
OBJDUMP	:= $(ARM_GCC)objdump
SIZE		:= $(ARM_GCC)size

# Common Options
CPU				:= -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16

# Assembler Options
AS_FLAGS	:= $(CPU) -x assembler $(CC_FLAGS)

# Compiler Options
CC_FLAGS	:= $(CPU) -pipe -std=c11
CC_FLAGS	+= -fno-common -fsigned-char -fmessage-length=0
CC_FLAGS	+= -Wall -Wextra -Wshadow
CC_FLAGS	+= -Os -ffunction-sections -fdata-sections
CC_FLAGS	+= -g3

# Linker Options
LD_FLAGS	:= $(CPU) -specs=nosys.specs
LD_FLAGS	+= -specs=nano.specs -u _printf_float -u _scanf_float
LD_FLAGS	+= -Wl,--gc-sections -Wl,-Map,$(PATH_LST)/$(BOARD)_$(TARGET).map,--cref
