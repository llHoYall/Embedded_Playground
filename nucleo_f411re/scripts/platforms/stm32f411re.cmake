################################################################################
#	@brief		cmake for stm32f411re platform.
#	@author		llHoYall <HoYa128@gmail.com>
#	@version	v1.0
#	@history
#		- 2018.12.05	Created.
################################################################################

file(GLOB PLATFORM_SRCS
	../../../drivers/bsp/${BOARD}/*.c
	../../../drivers/cmsis/${MCU}/*.c
	../../../drivers/stm32f4xx_hal/stm32f4xx_hal.c
	../../../drivers/stm32f4xx_hal/stm32f4xx_hal_adc.c
	../../../drivers/stm32f4xx_hal/stm32f4xx_hal_adc_ex.c
	../../../drivers/stm32f4xx_hal/stm32f4xx_hal_cortex.c
	../../../drivers/stm32f4xx_hal/stm32f4xx_hal_dma.c
	../../../drivers/stm32f4xx_hal/stm32f4xx_hal_dma_ex.c
	../../../drivers/stm32f4xx_hal/stm32f4xx_hal_dma2d.c
	../../../drivers/stm32f4xx_hal/stm32f4xx_hal_flash.c
	../../../drivers/stm32f4xx_hal/stm32f4xx_hal_flash_ex.c
	../../../drivers/stm32f4xx_hal/stm32f4xx_hal_flash_ramfunc.c
	../../../drivers/stm32f4xx_hal/stm32f4xx_hal_gpio.c
	../../../drivers/stm32f4xx_hal/stm32f4xx_hal_pwr.c
	../../../drivers/stm32f4xx_hal/stm32f4xx_hal_pwr_ex.c
	../../../drivers/stm32f4xx_hal/stm32f4xx_hal_rcc.c
	../../../drivers/stm32f4xx_hal/stm32f4xx_hal_rcc_ex.c
	../../../drivers/stm32f4xx_hal/stm32f4xx_hal_spi.c
)
