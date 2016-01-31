/**
  ******************************************************************************
  * File Name          : gpio.c
  * Description        : This file provides code for the configuration
  *                      of all used GPIO pins.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/** Configure pins as 
     PB13   ------> SPI2_SCK
		 itd ...
*/
void MX_GPIO_Init(void)
{

//  GPIO_InitTypeDef GPIO_InitStruct;

//  /* GPIO Ports Clock Enable */
//  __GPIOB_CLK_ENABLE();

////  /*Configure GPIO pins : PCPin PCPin PCPin PCPin 
////                           PCPin PCPin */
////  GPIO_InitStruct.Pin = NCS_MEMS_SPI_Pin|EXT_RESET_Pin|LD3_Pin|LD6_Pin 
////                          |LD4_Pin|LD5_Pin;
////  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
////  GPIO_InitStruct.Pull = GPIO_NOPULL;
////  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
////  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

////  /*Configure GPIO pins : PCPin PCPin */
////  GPIO_InitStruct.Pin = MEMS_INT1_Pin|MEMS_INT2_Pin;
////  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
////  GPIO_InitStruct.Pull = GPIO_NOPULL;
////  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

////  /*Configure GPIO pin : PtPin */
////  GPIO_InitStruct.Pin = B1_Pin;
////  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
////  GPIO_InitStruct.Pull = GPIO_NOPULL;
////  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

////  /*Configure GPIO pins : PA2 PA3 PA6 PA7 */
////  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_6|GPIO_PIN_7;
////  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
////  GPIO_InitStruct.Pull = GPIO_NOPULL;
////  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
////  GPIO_InitStruct.Alternate = GPIO_AF3_TSC;
////  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

////  /*Configure GPIO pins : PB0 PB1 */
////  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
////  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
////  GPIO_InitStruct.Pull = GPIO_NOPULL;
////  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
////  GPIO_InitStruct.Alternate = GPIO_AF3_TSC;
////  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

////  /*Configure GPIO pins : PB10 PB11 */
////  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
////  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
////  GPIO_InitStruct.Pull = GPIO_PULLUP;
////  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
////  GPIO_InitStruct.Alternate = GPIO_AF1_I2C2;
////  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

////  /*Configure GPIO pins : PB13 PB14 PB15 */
////  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
////  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
////  GPIO_InitStruct.Pull = GPIO_NOPULL;
////  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
////  GPIO_InitStruct.Alternate = GPIO_AF0_SPI2;
////  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

//  /*Configure GPIO pin : PB3 */
//  GPIO_InitStruct.Pin = GPIO_PIN_3;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
//  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

