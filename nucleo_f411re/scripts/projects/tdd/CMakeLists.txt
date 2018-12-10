################################################################################
#	@brief		cmake for TDD projects
#	@author		llHoYall <HoYa128@gmail.com>
#	@version	v1.0
#	@history
#		- 2018.12.05	Created.
################################################################################

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(PROJECT tdd)
set(MCU stm32f411re)
set(BOARD stm32f411re-nucleo)

set(LD_SCRIPT "${CMAKE_SOURCE_DIR}/drivers/cmsis/${MCU}/linker/STM32F411RETx_FLASH.ld")

include(../../tools/gcc.cmake)
include(../../platforms/stm32f411re.cmake)

file(GLOB TDD_SRCS
	../../../projects/${BOARD}_${PROJECT}/*.c
)

include_directories(
	../../../drivers/bsp/${BOARD}
	../../../drivers/cmsis/inc
	../../../drivers/cmsis/${MCU}
	../../../drivers/stm32f4xx_hal
	../../../drivers/stm32f4xx_hal/Legacy
	../../../utils
	../../../projects/${BOARD}_${PROJECT}
)

add_definitions(
	-DSTM32F411xE
	-DUSE_HAL_DRIVER
	-DNDEBUG
)

add_executable(${BOARD}_${PROJECT} ${PLATFORM_SRCS} ${TDD_SRCS})

target_link_libraries(${BOARD}_${PROJECT} ${CPU} -T ${LD_SCRIPT})

add_custom_command(
	OUTPUT ${BOARD}_${PROJECT}.bin
	DEPENDS ${BOARD}_${PROJECT}
	COMMAND ${CMAKE_OBJCOPY} -O binary ${BOARD}_${PROJECT} ${BOARD}_${PROJECT}.bin
)

add_custom_command(
	OUTPUT ${BOARD}_${PROJECT}.lst
	DEPENDS ${BOARD}_${PROJECT}
	COMMAND ${CMAKE_OBJCOPY} -Sdh ${BOARD}_${PROJECT} > ${BOARD}_${PROJECT}.lst
)
