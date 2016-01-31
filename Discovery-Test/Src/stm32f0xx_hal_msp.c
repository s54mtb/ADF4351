/**
  ******************************************************************************
  * File Name          : stm32f0xx_hal_msp.c
  * Description        : This file provides code for the MSP Initialization 
  *                      and de-Initialization codes.
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"

/**
  * Initializes the Global MSP.
  */
void HAL_MspInit(void)
{
  __SYSCFG_CLK_ENABLE();
  /* System interrupt init*/
  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

