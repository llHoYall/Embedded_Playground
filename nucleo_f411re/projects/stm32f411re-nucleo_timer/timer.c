/*******************************************************************************
 * @file		bsp/stm32f401re-nucleo/timer.c
 * @brief		This source file is for timer.
 * @author	HoYa	<hoya128@gmail.com>
 *******************************************************************************
 * @version	v1.0
 * @note
 *	- 2018.01.31	Created.
 ******************************************************************************/

/* Include Headers -----------------------------------------------------------*/
// User Header
#include "timer.h"

/* Global Variables ----------------------------------------------------------*/
TIM_HandleTypeDef	hTim;

/* System Functions ----------------------------------------------------------*/
HAL_StatusTypeDef	HAL_InitTick(uint32_t tick_priority) {
	RCC_ClkInitTypeDef clock_config;
	uint32_t	tim_clock;
	uint32_t	prescaler = 0;
	uint32_t	prescaler_value = 0;
	uint32_t	latency;

	__HAL_RCC_TIM5_CLK_ENABLE();

	HAL_NVIC_SetPriority(TIM5_IRQn, TICK_INT_PRIORITY, 0);
	HAL_NVIC_EnableIRQ(TIM5_IRQn);
	HAL_NVIC_SetPriority(TIM5_IRQn, tick_priority, 0);
	HAL_RCC_GetClockConfig(&clock_config, &latency);

	prescaler = clock_config.APB1CLKDivider;
	if (prescaler == 0) {
		tim_clock = HAL_RCC_GetPCLK1Freq();
	}
	else {
		tim_clock = HAL_RCC_GetPCLK1Freq() * 2;
	}
	prescaler_value = (uint32_t)((tim_clock / 1000000) - 1);

	hTim.Instance = TIM5;
	hTim.Init.Period = (1000000 / 1000) - 1;
	hTim.Init.Prescaler = prescaler_value;
	hTim.Init.ClockDivision = 0;
	hTim.Init.CounterMode = TIM_COUNTERMODE_UP;
	if (HAL_TIM_Base_Init(&hTim) == HAL_OK) {
		return HAL_TIM_Base_Start_IT(&hTim);
	}

	return HAL_OK;
}

void HAL_SuspendTick(void) {
	__HAL_TIM_DISABLE_IT(&hTim, TIM_IT_UPDATE);
}

void HAL_ResumeTick(void) {
	__HAL_TIM_ENABLE_IT(&hTim, TIM_IT_UPDATE);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {
	(void)htim;

	HAL_IncTick();
}
