/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : PLL Main program body
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"
#include "spi.h"
#include "gpio.h"
#include "adf4351.h"

extern SPI_HandleTypeDef hspi1;
void SystemClock_Config(void);
extern HAL_StatusTypeDef adf4351_write(uint32_t data);


/***************************************************************************//**
 * @brief Writes 4 bytes of data to ADF4351.
 * @param data - Data value to write.
 * @retval SPI status
*******************************************************************************/
HAL_StatusTypeDef adf4351_write(uint32_t data)
{
  return SPI_SendWord(data, &hspi1);
}


void PLL_Sync(void)
{
		int i;

	for (i=0; i<6; i++)
	{
    adf4351_write(ADF4351_GetRegisterBuf(5-i));	//	Write registers to PLL chip
	}
}


int main(void)
{
//	uint8_t test[4] = {0x12,0x34,0x56,0x78};
  /* MCU Configuration----------------------------------------------------------*/
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */

	double calcfreq;
	double CurrentFreq = 3402e6;
	
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();

  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
 
	/* Prepare the PLL */

	ADF4351_Init();
	ADF4351_Reg1.b.PhaseAdjust = ADF4351_DISABLE;
	ADF4351_Reg1.b.PhaseVal = 1;
	ADF4351_Reg1.b.Prescaler = ADF4351_PRESCALER_4_5;
	
	ADF4351_Reg2.b.CounterReset = ADF4351_DISABLE;
	ADF4351_Reg2.b.RDiv2 = ADF4351_REFDIV_2;
	ADF4351_Reg2.b.RMul2 = ADF4351_REFMUL_1;
	ADF4351_Reg2.b.CPCurrent = ADF4351_CPCURRENT_1_88;
	ADF4351_Reg2.b.CPTristate = ADF4351_DISABLE;
	ADF4351_Reg2.b.DoubleBuffer  = ADF4351_DISABLE;
	ADF4351_Reg2.b.LockFunction = ADF4351_LDF_FRAC;
	ADF4351_Reg2.b.LockPrecision = ADF4351_LDP_10NS;
	ADF4351_Reg2.b.LowNoiseSpur = ADF4351_LOW_NOISE_MODE;
	ADF4351_Reg2.b.MuxOut = ADF4351_MUX_THREESTATE;
	ADF4351_Reg2.b.PhasePolarity = ADF4351_POLARITY_POSITIVE;
	ADF4351_Reg2.b.PowerDown = ADF4351_DISABLE;
	ADF4351_Reg2.b.RCountVal = 1;
	
	ADF4351_Reg3.b.AntibacklashW = ADF4351_ABP_6NS;
	ADF4351_Reg3.b.BandSelMode = ADF4351_BANDCLOCK_LOW;
	ADF4351_Reg3.b.ChargeCh = ADF4351_DISABLE;
	ADF4351_Reg3.b.ClkDivMod = ADF4351_CLKDIVMODE_OFF;
	ADF4351_Reg3.b.ClkDivVal = 150;
	ADF4351_Reg3.b.CsrEn = ADF4351_DISABLE;
	
	ADF4351_Reg4.b.AuxEnable = ADF4351_DISABLE;
	ADF4351_Reg4.b.Mtld = ADF4351_DISABLE;
	ADF4351_Reg4.b.OutEnable = ADF4351_ENABLE;
	ADF4351_Reg4.b.OutPower = ADF4351_POWER_PLUS5DB;
	ADF4351_Reg4.b.VcoPowerDown =  ADF4351_DISABLE;
	ADF4351_Reg4.b.Feedback = ADF4351_FEEDBACK_FUNDAMENTAL;

	ADF4351_Reg5.b.LdPinMode = ADF4351_LD_PIN_DIGITAL_LOCK;
	
/* Infinite loop */
  while (1)
  {
		UpdateFrequencyRegisters(CurrentFreq, 50000000.0, 12500, 1, 1, &calcfreq); 	
		PLL_Sync();
		HAL_Delay(2000);
		CurrentFreq += 1e6;
		if (CurrentFreq > 3410e6) CurrentFreq = 3402e6;
  }

}


/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1);

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
}

#endif

