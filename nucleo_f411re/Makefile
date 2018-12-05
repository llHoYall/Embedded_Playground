################################################################################
#	@brief		Top makefile
#	@author		llHoYall <HoYa128@gmail.com>
#	@version	v1.0
#	@history
#		- 2018.12.04	Created.
################################################################################

# Special Targets -------------------------------------------------------------#
.EXPORT_ALL_VARIABLES:

# Definitions -----------------------------------------------------------------#
OS		:= LINUX
JOB		:= -j$(shell getconf _NPROCESSORS_ONLN)		# for MAC/Linux
# JOB		:= -j$(NUMBER_OF_PROCESSORS)		# for Windows
OPT		:= --no-print-directory

# Include Makefiles -----------------------------------------------------------#
include scripts/path.mk

# Targets ---------------------------------------------------------------------#
all: make_directory
	@echo === [ BUILD ALL ] ===
	@make $(JOB) $(OPT) -f script/stm32f411re-nucleo_freertos/Makefile
	@make $(JOB) $(OPT) -f script/stm32f411re-nucleo_hos/Makefile
	@make $(JOB) $(OPT) -f script/stm32f411re-nucleo_tdd/Makefile
	@make $(JOB) $(OPT) -f script/stm32f411re-nucleo_timer/Makefile
	@make $(JOB) $(OPT) -f script/stm32f411re-nucleo_uart/Makefile
	@echo === [ BUILD END ] ===

stm32f411re-nucleo_freertos: make_directory
	@echo === [ BUILD FreeRTOS ] ===
	@make $(JOB) $(OPT) -f script/stm32f411re-nucleo_freertos/Makefile
	@echo === [ BUILD END ] ==

stm32f411re-nucleo_hos: make_directory
	@echo === [ BUILD hOS ] ===
	@make $(JOB) $(OPT) -f script/stm32f411re-nucleo_hos/Makefile
	@echo === [ BUILD END ] ==

stm32f411re-nucleo_tdd: make_directory
	@echo === [ BUILD TDD ] ===
	@make $(JOB) $(OPT) -f scripts/projects/tdd.mk
	@echo === [ BUILD END ] ==

stm32f411re-nucleo_timer: make_directory
	@echo === [ BUILD TIMER ] ===
	@make $(JOB) $(OPT) -f script/stm32f411re-nucleo_timer/Makefile
	@echo === [ BUILD END ] ==

stm32f411re-nucleo_uart: make_directory
	@echo === [ BUILD UART ] ===
	@make $(JOB) $(OPT) -f script/stm32f411re-nucleo_uart/Makefile
	@echo === [ BUILD END ] ==

make_directory:
ifeq ($(OS),WINDOWS)
	@mkdir -p $(subst /,\,$(PATH_BUILD))
	@mkdir -p $(subst /,\,$(PATH_OBJ))
	@mkdir -p $(subst /,\,$(PATH_DEP))
	@mkdir -p $(subst /,\,$(PATH_LIB))
	@mkdir -p $(subst /,\,$(PATH_LST))
	@mkdir -p $(subst /,\,$(PATH_BIN))
else
	@mkdir -p $(PATH_BUILD)
	@mkdir -p $(PATH_OBJ)
	@mkdir -p $(PATH_DEP)
	@mkdir -p $(PATH_LIB)
	@mkdir -p $(PATH_LST)
	@mkdir -p $(PATH_BIN)
endif

clean:
	@echo === [ CLEAN ] ===
	@rm -rf $(PATH_BUILD)
