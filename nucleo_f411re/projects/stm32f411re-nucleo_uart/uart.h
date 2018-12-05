/*******************************************************************************
 * @file		apps/uart/uart.h
 * @brief		This header file is for uart communications.
 * @author	HoYa <hoya128@gmail.com>
 *******************************************************************************
 * @version	v1.0
 * @note
 *	- 2018.01.04	Created.
 ******************************************************************************/

#ifndef __UART_H__
#define __UART_H__

/* Include Headers -----------------------------------------------------------*/
// Standard	Header
#include <stdio.h>
// System	Header
#include "stm32f4xx_hal.h"
#include "stm32f4xx_nucleo.h"

/* Definitions ---------------------------------------------------------------*/
// Definitions for USARTx clock resources
#define USARTx                          USART2
#define USARTx_CLK_ENABLE()             __HAL_RCC_USART2_CLK_ENABLE()
#define USARTx_RX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOA_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOA_CLK_ENABLE()
#define USARTx_FORCE_RESET()            __HAL_RCC_USART2_FORCE_RESET()
#define USARTx_RELEASE_RESET()          __HAL_RCC_USART2_RELEASE_RESET()

// Definitions for USARTx Pins
#define USARTx_TX_PIN                   GPIO_PIN_2
#define USARTx_TX_GPIO_PORT             GPIOA
#define USARTx_TX_AF                    GPIO_AF7_USART2
#define USARTx_RX_PIN                   GPIO_PIN_3
#define USARTx_RX_GPIO_PORT             GPIOA
#define USARTx_RX_AF                    GPIO_AF7_USART2

/* Enumerations --------------------------------------------------------------*/
// Status
typedef enum _eUART_STATUS {
	eUART_STATUS_SUCCESS = 0x00,
	eUART_STATUS_INIT_FAIL,
} eUART_STATUS;

/* Global Variables ----------------------------------------------------------*/
extern UART_HandleTypeDef	hUart2;

/* APIs ----------------------------------------------------------------------*/
/**
 * @brief				Initialize UART.
 * @param[in]		baudrate: baudrate of uart. ex) 115200
 * @retval			status. SUCCESS or INIT_FAIL.
 */
eUART_STATUS uart_init(uint32_t baudrate);

#endif
