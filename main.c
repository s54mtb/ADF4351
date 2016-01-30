/**
 * @file     main.c
 * @brief    Testing ADF4351 driver
 * @version  V0.00
 * @date     18. January 2016
 *
 * @note
 *
 */

#include "stm32f0xx.h"                  // Device header
#include "adf4351.h"



int main(void)
{
  static uint32_t reg0, reg1;  // static... Avoid compiler optimisation for checking values with debugger
	double calcfreq;
	
	// Just testing - some initial values
	ADF4351_Reg2->b.RCountVal = 1;
	ADF4351_Reg2->b.RDiv2 = ADF4351_REFDIV_2;
	ADF4351_Reg2->b.RMul2 = ADF4351_REFMUL_1;
	ADF4351_Reg4->b.Feedback = ADF4351_FEEDBACK_FUNDAMENTAL;

	ADF4351_Reg0->b.ControlBits = 0;
	ADF4351_Reg1->b.ControlBits = 1;
	ADF4351_Reg2->b.ControlBits = 2;
	ADF4351_Reg3->b.ControlBits = 3;
	ADF4351_Reg4->b.ControlBits = 4;
	ADF4351_Reg5->b.ControlBits = 5;
	
	
	UpdateFrequencyRegisters(1234000000.0, 50000000.0, 12500, 1, 1, &calcfreq);
	reg0 = ADF4351_GetRegisterBuf(0);
	reg1 = ADF4351_GetRegisterBuf(1);
	
	while (1);
	
}


