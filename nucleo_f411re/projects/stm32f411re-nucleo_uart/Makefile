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

TARGET		:= hUart
MCU				:= stm32f401re
BOARD			:= stm32f401re-nucleo
APP				:= uart

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

# -mfpu=fpv4-sp-d16: floating point version 4 single precision d registers 16
CPU					:= -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16
#	-x <language>: Specify explicitly the language for the following input files.
#		assembler
#		assemler-with-cpp
AS_FLAGS		= $(CPU) -x assembler $(CC_FLAGS)
# -pipe: Use pipes rather than temporary files for communication between the
#  			 various stages of compilation.
# -ffreestanding: Assert that compilation targets a freestanding environment.
#  								This implies -fno-builtin. This is equivalent to -fno-hosted.
# -fno-common: In C code, controls the placement of uninitialized global
#  						 variables. The option specifies that the compiler should place
#  						 uninitialized global variables in the data section of the object
#  						 file, rather than generating them as common blocks.
# -fsigned-char: Let the type 'char' be signed, like 'signed char'.
# -fmessage-length=n: Try to format error messages so that they fit on lines
#  										of about n characters. If n is zero, then no
#  										line-wrapping is done; each error message appears on a
#  										single line.
# -Wall: This enables all the warnings about constructions that some users
#  			 consider questionable, and that are easy to avoid, even in conjunction
#  			 with macros.
# -Wextra: This enables some extra warning flags that are not enabled by -Wall.
# -Wshadow: Warn whenever a local variable or type declaration shadows another
#  					variables, parameter, type, class member (in C++), or instance
#  					variable (in Objective-C) or whenever a built-in function is
#  					shadowed.
# -Werror: Make all warnings into errors.
# -Os: Optimize for size. '-Os' enables all '-O2' optimizations that do not
#  		 typically increase code size.
# -ffunction-sections, -fdata-sections:
#  	Place each function or data item into its own section in the output file
#  	if the target supports arbitrary sections.
# -glevel: Request debugging information and also use level to specify how much
#  				 information. The default level is 2.
# 	'-g3': Level3 includes extra information, such as all the macro definitions
# 				 present in the program.
# -M: Instead of outputting the result of preprocessing, output a rule suitable
#  		for make describing the dependencies of the main source file.
# -MM: Like '-M' but do not mention header files that are found in system
# 		 header directories, nor header files that are included, directly or
# 		 indirectly, from such a header.
# -MF <file>: When used with '-M' or '-MM', specifies a file to write the
#  						dependencies to. When used with the driver options '-MD' or
#  						'-MMD', '-MF' overrides the default dependency output file.
# -MP: This option instructs CPP to add a phony target for each dependency
#  		 other than the main file, causing each to depend on nothing.
# -MT <target>: Change the target of the rule emitted by dependency generation.
# -MD: '-MD' is equivalent to '-M -MF <file>', except that '-E' is not implied.
# -MMD: Like '-MD' except mention only user header files, not system header
#  			files.
CC_FLAGS	:= $(CPU) -pipe -std=c11	\
						 -fno-common -fsigned-char -fmessage-length=0	\
						 -Wall -Wextra -Wshadow	\
						 -Os -ffunction-sections -fdata-sections	\
						 -g3
# -specs
#  	nosys.specs: Use newlib.
#  	nano.specs: Reduce code size but does not allow use float in printf.
#  	rdimon.specs: Enable semihosting
# -Xlinker, -Wl
#  	'-Xlinker': Pass options as an option to the linker.
#  	'-Wl': Pass options as an option to the linker. If option contains commas,
#  				 it is split into multiple options at the commas. You can use this
#  				 syntax to pass an argument to the option.
#		'-Xlinker -Map=$(TARGET).map' same as '-Wl,-Map,$(TARGET).map'
#		'--cref': Output a cross reference table.
# --gc-sections: Enable garbage collection of unused input sections.
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

# If you want make to simply ignore a makefile which does not exist or cannot
# be remade, with no error message, use the '-include' directive.
ifneq ($(MAKECMDGOALS), clean)
-include $(DEPS)
endif
