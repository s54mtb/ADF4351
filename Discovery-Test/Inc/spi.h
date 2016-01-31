/**
  ******************************************************************************
  * File Name          : SPI.h
  * Description        : This file provides code for the configuration
  *                      of the SPI instances.
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __spi_H
#define __spi_H
#ifdef __cplusplus
 extern "C" {
#endif
#include "stm32f0xx_hal.h"

extern SPI_HandleTypeDef hspi1;
void MX_SPI1_Init(void);
HAL_StatusTypeDef SPI_SendWord(uint32_t data, SPI_HandleTypeDef* hspi);

#ifdef __cplusplus
}
#endif
#endif /*__ spi_H */
