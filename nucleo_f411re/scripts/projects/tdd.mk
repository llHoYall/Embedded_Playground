################################################################################
#	@brief		Makefile for TDD projects
#	@author		llHoYall <HoYa128@gmail.com>
#	@version	v1.0
#	@history
#		- 2018.12.04	Created.
################################################################################

# Special Targets -------------------------------------------------------------#
.EXPORT_ALL_VARIABLES:

# Definitions -----------------------------------------------------------------#
TARGET		:= tdd
MCU				:= stm32f411re
BOARD			:= stm32f411re-nucleo
PROJECT		:= tdd

# Include Makefiles -----------------------------------------------------------#
include scripts/tools/gcc.mk
include scripts/platforms/stm32f411re.mk
include scripts/bsp.mk

# Definitions -----------------------------------------------------------------#
TDD_SRCS	+= ./projects/$(BOARD)_$(PROJECT)/stm32f4xx_it.c
TDD_SRCS	+= ./projects/$(BOARD)_$(PROJECT)/main.c

TDD_INCS	:= $(PLATFORM_INCS)
TDD_INCS	+= -I./utils
TDD_INCS	+= -I./projects/$(BOARD)_$(PROJECT)

TDD_DEFS	:= $(PLATFORM_DEFS)
TDD_DEFS	+= -DNDEBUG

TDD_OBJS	:= $(patsubst %.c,$(PATH_OBJ)/$(PROJECT)/%.o,$(notdir $(TDD_SRCS)))

TDD_DEPS	:= $(patsubst %.c,$(PATH_DEP)/$(PROJECT)/%.d,$(notdir $(TDD_SRCS)))

vpath %.s $(sort $(dir $(STARTUP)))
vpath %.c $(sort $(dir $(PLATFORM_SRCS)))
vpath %.c $(sort $(dir $(TDD_SRCS)))

# Targets ---------------------------------------------------------------------#
all: make_directory $(PATH_BIN)/$(BOARD)_$(TARGET).bin $(PATH_LST)/$(BOARD)_$(TARGET).lst

make_directory:
ifeq ($(OS),WINDOWS)
	@mkdir -p $(subst /,\,$(PATH_OBJ)/$(BOARD))
	@mkdir -p $(subst /,\,$(PATH_OBJ)/$(PROJECT))
	@mkdir -p $(subst /,\,$(PATH_DEP)/$(BOARD))
	@mkdir -p $(subst /,\,$(PATH_DEP)/$(PROJECT))
else
	@mkdir -p $(PATH_OBJ)/$(BOARD)
	@mkdir -p $(PATH_OBJ)/$(PROJECT)
	@mkdir -p $(PATH_DEP)/$(BOARD)
	@mkdir -p $(PATH_DEP)/$(PROJECT)
endif

$(PATH_BIN)/$(BOARD)_$(TARGET).bin: $(PATH_BIN)/$(BOARD)_$(TARGET).elf
	@$(OBJCOPY) -O binary -S $< $@
	@du -ch $(BIN_DIR)/$(BOARD)_$(TARGET).bin

$(PATH_LST)/$(BOARD)_$(TARGET).lst: $(PATH_BIN)/$(BOARD)_$(TARGET).elf
	@$(OBJDUMP) -Sdh $< > $@

$(PATH_BIN)/$(BOARD)_$(TARGET).elf: $(PLATFORM_OBJS) $(TDD_OBJS)
	@$(LD) $(LD_FLAGS) -T $(LD_SCRIPT) -o $@ $^
	@$(SIZE) --format=berkeley $@

$(PATH_OBJ)/$(BOARD)/%.o: %.s
	@$(AS) $(AS_FLAGS) -c $< -o $@

$(PATH_OBJ)/$(BOARD)/%.o: %.c
	@echo Compiling... $<
	@$(CC) $(CC_FLAGS) $(TDD_DEFS) $(TDD_INCS) -c $< -o $@
	@$(CC) $(CC_FLAGS) $(TDD_DEFS) $(TDD_INCS) -M -MP -MT $@ -MF $(PATH_DEP)/$(BOARD)/$(*F).d $<

$(PATH_OBJ)/$(PROJECT)/%.o: %.c
	@echo Compiling... $<
	@$(CC) $(CC_FLAGS) $(TDD_DEFS) $(TDD_INCS) -c $< -o $@
	@$(CC) $(CC_FLAGS) $(TDD_DEFS) $(TDD_INCS) -M -MP -MT $@ -MF $(PATH_DEP)/$(PROJECT)/$(*F).d $<

clean:
	@echo "\033[31m [ CLEAN - $(BOARD)_$(APP) ]\033[0m"
	@rm -rf $(BIN_DIR) $(BUILD_DIR)

ifneq ($(MAKECMDGOALS), clean)
-include $(DEPS)
endif
