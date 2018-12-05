################################################################################
#	@file			CMakeLists.txt
#	@brief		This is a cmake build script for <stm32f401re-nucleo>.
#	@author		llHoYall <HoYa128@gmail.com>
################################################################################
#	@version	v1.0
#	@note
#		- 2018.01.08	Created.
################################################################################

cmake_minimum_required (VERSION 3.5)

set (CMAKE_SYSTEM_NAME Generic)
set (CMAKE_SYSTEM_PROCESSOR arm)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set (CMAKE_ASM_COMPILER arm-none-eabi-as)
set (CMAKE_C_COMPILER arm-none-eabi-gcc)
set (CMAKE_OBJCOPY arm-none-eabi-objcopy)
set (CMAKE_OBJDUMP arm-none-eabi-objdump)
set (CMAKE_SIZE arm-none-eabi-size)

set (TARGET hUart)
set (MCU stm32f401re)
set (BOARD stm32f401re-nucleo)
set (APP uart)

set (CMAKE_ASM_FLAGS
	-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16
)
set (CMAKE_C_FLAGS
	-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16
	-fno-common -fsigned-char -fmessage-length=0
	-Wall -Wextra -Wshadow
	-Os -ffunction-sections -data-sections
	-g3
	-std=c11
)
set (CMAKE_EXE_LINKER_FLAGS
	-spec=nosys.specs -spec=nano.specs -u _printf_float -u _scanf_float
	-Wl,--gc-sections -Wl,-map=${TARGET}.map,--cref
)

add_definitions (
	-DNDEBUG
	-DSTM32F401xE -DUSE_HAL_DRIVER -DUSE_FULL_ASSERT
	-DUSE_STM32F4XX_NUCLEO
)

project (${TARGET})

include_directories (
	drivers/${MCU}/cmsis
	drivers/${MCU}/hal
	bsp/${BOARD}
	projects/${BOARD}
	apps/${APP}
)

file (GLOB STARTUP
	drivers/${MCU}/startup/*.s
)
message (STATUS "[DBG]: ${STARTUP})
file (GLOB CMSIS_SRCS
	drivers/${MCU}/cmsis/*.c
	drivers/${MCU}/hal/*.c
)
file (GLOB BSP_SRCS
	bsp/${BOARD}/*.c
)
file (GLOB APP_SRCS
	projects/${BOARD}/*.c
	apps/uart/*.c
)
message (STATUS "[DBG]: ${APP_SRCS})

set (LINKER_SCRIPT drivers/${MCU}/linker/STM32F401VEHx_FLASH.ld)

add_executable (${TARGET}.elf ${STARTUP} ${CMSIS_SRCS} ${BSP_SRCS} ${APP_SRCS} ${LINKER_SCRIPT})

add_custom_target (${TARGET}.bin
	DEPENDS ${TARGET}.elf
	COMMAND ${CMAKE_OBJCOPY} -O binary ${TARGET}.elf ${TARGET}.bin
)

add_custom_target (${TARGET}.lst
	DEPENDS ${TARGET}.elf
	COMMAND ${CMAKE_OBJDUMP} -Sdh ${TARGET}.elf > ${TARGET}.lst
)
