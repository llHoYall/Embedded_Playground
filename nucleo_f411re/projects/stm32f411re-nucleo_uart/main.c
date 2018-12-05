/*******************************************************************************
 * @file		apps/uart/main.c
 * @brief		This application is a simple uart example.
 * @author	HoYa <hoya128@gmail.com>
 *******************************************************************************
 * @version	v1.0
 * @note
 *	- 2018.01.02	Created.
 ******************************************************************************/

/* Include Headers -----------------------------------------------------------*/
// Standard
#include <stdio.h>
// System Header
#include "stm32f4xx_hal.h"
#include "stm32f4xx_nucleo.h"
// User Header
#include "uart.h"

/* Private Function Prototypes -----------------------------------------------*/
static void SystemClock_Config(void);

/* Main Function -------------------------------------------------------------*/
int main(void) {
	HAL_Init();
	SystemClock_Config();

	BSP_LED_Init(LED2);
	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);
	uart_init(115200);

	puts("");
	puts("Hello World!\r");

	// Test getchar()
	uint8_t ch;
	printf("Input char: ");
	ch = getchar();
	puts("\r");
	printf("Your input is %c.\r\n", ch);

	// Test floating point printf/scanf
	float f;
	printf("Input float number: ");
	scanf("%f", &f);
	puts("\r");
	printf("Your input is %f.\r\n", f);

	char test[] = "This is a test string\r\n";
	HAL_UART_Transmit(&hUart2, (uint8_t*)test, sizeof(test), 0xffff);
	HAL_UART_Transmit_IT(&hUart2, (uint8_t*)test, sizeof(test));

	while (1) {
		BSP_LED_Toggle(LED2);
		if (BSP_PB_GetState(BUTTON_USER) == RESET) {
			puts("Pressed\r\n");
		}

		HAL_Delay(500);
	}

	return 0;
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
	(void)file;
	(void)line;

	while (1) {
	}
}
#endif

/* Private Functions ---------------------------------------------------------*/
static void SystemClock_Config(void) {
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  // Enable Power Control clock.
  __HAL_RCC_PWR_CLK_ENABLE();

  // The voltage scaling allows optimizing the power consumption when the
	// device is clocked below the maximum system frequency, to update the
	// voltage scaling value regarding system frequency refer to product
	// datasheet.
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  // Enable HSI Oscillator and activate PLL with HSI as source.
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 0x10;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		return;
  }

  // Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
	// clocks dividers.
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |	\
																 RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
		return;
  }
}
