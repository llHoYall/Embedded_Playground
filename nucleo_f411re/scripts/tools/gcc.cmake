################################################################################
# @brief		cmake for arm-none-eabi- tools
# @author		HoYa <hoya128@nextchip.com>
# @version	v1.0
# @history
#		- 2018.12.05	Created.
################################################################################

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_ASM_COMPILER "arm-none-eabi-gcc")
set(CMAKE_C_COMPILER "arm-none-eabi-gcc")
set(CMAKE_LINKER "arm-none-eabi-gcc")
set(CMAKE_OBJCOPY "arm-none-eabi-objcopy" CACHE INTERNAL "objcopy tool")
set(CMAKE_OBJDUMP "arm-none-eabi-objdump" CACHE INTERNAL "objdump tool")

set(CPU "-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16")

set(CMAKE_ASM_FLAGS "${CPU} -x assembler" CACHE INTERNAL "asm compiler flags")
set(CMAKE_C_FLAGS "${CPU} -pipe -std=c11 -fno-common -fsigned-char -fmessage-length=0 -Wall -Wextra -Wshadow -Os -ffunction-sections -fdata-sections -g3" CACHE INTERNAL "c compiler flags")
set(CMAKE_EXE_LINKER_FLAGS "${CPU} -specs=nosys.specs -specs=nano.specs -u _printf_float -u _scanf_float -Wl,--gc-sections -Wl,-Map,./${BOARD}_${PROJECT}.map,--cref" CACHE INTERNAL "linker flags")
