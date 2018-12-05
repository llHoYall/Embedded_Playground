################################################################################
#	@file			Makefile
#	@brief		This is a makefile build script for <stm32f401re-nucleo>.
#	@author		llHoYall <HoYa128@gmail.com>
################################################################################
#	@version	v1.0
#	@note
#		- 2018.01.02	Created.
################################################################################

.EXPORT_ALL_VARIABLES:

ARM_GCC	:= arm-none-eabi-
AS			:= $(ARM_GCC)gcc
CC			:= $(ARM_GCC)gcc
LD			:= $(ARM_GCC)gcc
OBJCOPY	:= $(ARM_GCC)objcopy
OBJDUMP	:= $(ARM_GCC)objdump
SIZE		:= $(ARM_GCC)size

TARGET		:= hTimer
MCU				:= stm32f401re
BOARD			:= stm32f401re-nucleo
APP				:= timer

BUILD_DIR	:= projects/$(BOARD)_$(APP)/build
BIN_DIR		:= projects/bin
OBJ_DIR		:= $(BUILD_DIR)/obj
DEP_DIR		:= $(BUILD_DIR)/dep

include scripts/build/platform.mk
include scripts/build/bsp.mk

SRCS		 = $(PLATFORM_SRCS)
SRCS		+= $(BSP_SRCS)
SRCS		+= projects/$(BOARD)_$(APP)/stm32f4xx_it.c	\
					 projects/$(BOARD)_$(APP)/uart.c	\
					 projects/$(BOARD)_$(APP)/timer.c	\
					 projects/$(BOARD)_$(APP)/main.c

vpath %.s $(sort $(dir $(STARTUP)))
vpath %.c $(sort $(dir $(SRCS)))

OBJS		:= $(patsubst %.s,$(OBJ_DIR)/%.o,$(notdir $(STARTUP)))	\
					 $(patsubst %.c,$(OBJ_DIR)/%.o,$(notdir $(SRCS)))
DEPS		:= $(patsubst %.c,$(DEP_DIR)/%.d,$(notdir $(SRCS)))

INCS		 = $(PLATFORM_INCS)
INCS		+= $(BSP_INCS)
INCS		+= -Iprojects/$(BOARD)_$(APP)

DEFS		 = -DNDEBUG
DEFS		+= $(PLATFORM_DEFS)
DEFS		+= $(BSP_DEFS)

CPU					:= -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16
AS_FLAGS		= $(CPU) -x assembler $(CC_FLAGS)
CC_FLAGS	:= $(CPU) -pipe -std=c11	\
						 -fno-common -fsigned-char -fmessage-length=0	\
						 -Wall -Wextra -Wshadow	\
						 -Os -ffunction-sections -fdata-sections	\
						 -g3
LD_FLAGS		:= $(CPU) -specs=nosys.specs	\
							 -specs=nano.specs -u _printf_float -u _scanf_float	\
							 -Wl,--gc-sections -Wl,-Map,$(OBJ_DIR)/$(TARGET).map,--cref

all: make_directory $(BIN_DIR)/$(TARGET).bin $(OBJ_DIR)/$(TARGET).lst

make_directory:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(DEP_DIR)

$(BIN_DIR)/$(TARGET).bin: $(BIN_DIR)/$(TARGET).elf
	@$(OBJCOPY) -O binary -S $< $@
	@du -ch $(BIN_DIR)/$(TARGET).bin

$(OBJ_DIR)/$(TARGET).lst: $(BIN_DIR)/$(TARGET).elf
	@$(OBJDUMP) -Sdh $< > $@

$(BIN_DIR)/$(TARGET).elf: $(OBJS)
	@$(LD) $(LD_FLAGS) -T $(LD_SCRIPT) -o $@ $^
	@$(SIZE) --format=berkeley $@

$(OBJ_DIR)/%.o: %.s
	@$(AS) $(AS_FLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: %.c
	@$(CC) $(CC_FLAGS) $(DEFS) $(INCS) -c $< -o $@
	@$(CC) $(CC_FLAGS) $(DEFS) $(INCS) -M -MP -MT $@ -MF $(DEP_DIR)/$(notdir $(basename $<).d) $<

clean:
	@echo "\033[31m [ CLEAN - $(BOARD)_$(APP) ]\033[0m"
	@rm -rf $(BIN_DIR) $(BUILD_DIR)

ifneq ($(MAKECMDGOALS), clean)
-include $(DEPS)
endif
