/**
 * @file     adf4351.c
 * @brief    ADF4351 driver 
 * @version  V0.00
 * @date     18. January 2016
 *
 * @note
 *
 */

#include "stm32f0xx.h"                  // Device header
#include "adf4351.h"
#include <math.h>

/**
 * \brief Buffer for ADF4351 registers 
 *
 */
volatile uint32_t ADF4351_Reg[6];


/**
 * \brief Pointers to ADF4351 register buffer 
 *
 */
ADF4351_Reg0_t *ADF4351_Reg0 = (ADF4351_Reg0_t *) &ADF4351_Reg[0];
ADF4351_Reg1_t *ADF4351_Reg1 = (ADF4351_Reg1_t *) &ADF4351_Reg[1];
ADF4351_Reg2_t *ADF4351_Reg2 = (ADF4351_Reg2_t *) &ADF4351_Reg[2];
ADF4351_Reg3_t *ADF4351_Reg3 = (ADF4351_Reg3_t *) &ADF4351_Reg[3];
ADF4351_Reg4_t *ADF4351_Reg4 = (ADF4351_Reg4_t *) &ADF4351_Reg[4];
ADF4351_Reg5_t *ADF4351_Reg5 = (ADF4351_Reg5_t *) &ADF4351_Reg[5];


/**  \brief Private Function Prototypes
  * 
  */
ADF4351_RFDIV_t ADF4351_Select_Output_Divider(double RFoutFrequency)
{
	// Select divider
	if (RFoutFrequency >= 2200000000.0) return ADF4351_RFDIV_1;
	if (RFoutFrequency < 2200000000.0) return ADF4351_RFDIV_2;
	if (RFoutFrequency < 1100000000.0) return ADF4351_RFDIV_4;
	if (RFoutFrequency < 550000000.0) return ADF4351_RFDIV_8;
	if (RFoutFrequency < 275000000.0) return ADF4351_RFDIV_16;
	if (RFoutFrequency < 137500000.0) return ADF4351_RFDIV_32;
  return ADF4351_RFDIV_64;
}

// greatest common denominator - euclid algo w/o recursion
int gcd_iter(uint32_t u, uint32_t v) {
  uint32_t t;
  while (v) {
    t = u; 
    u = v; 
    v = t % v;
  }
  return u ;
}


/**
  *  \brief Main function to calculate register values based on required PLL output
  * 	
  * @param  RFout: 								Required PLL output frequency in Hz
  * 				REFin:								Reference clock in Hz
  * 				OutputChannelSpacing:	Output channel spacing in Hz
  * 				gcd:									calculate CGD (1) or not (0)
  * 				AutoBandSelectClock:	automatic calc of band selection clock
  * @paramOut  RFoutCalc: 				Calculated actual output frequency in Hz
  * @retval 0=OK, or Error code (ADF4351_ERR_t)
  */
ADF4351_ERR_t UpdateFrequencyRegisters(double RFout, double REFin, double OutputChannelSpacing, int gcd, int AutoBandSelectClock, double *RFoutCalc )
{
	uint16_t 		OutputDivider;
	uint32_t 		temp;
	double			PFDFreq;							// PFD Frequency in Hz
	uint16_t 		Rcounter;							// R counter value
	int 				RefDoubler;  					// ref. doubler
	int 				RefD2;			 					// ref. div 2
  double 			N;
	uint16_t		INT,MOD,FRAC;
	uint32_t    D;
  double 			BandSelectClockDivider;
  double 			BandSelectClockFrequency;

	
	// Calculate N, INT, FRAC, MOD

	RefD2 = ADF4351_Reg2->b.RDiv2 + 1;					// 1 or 2
	RefDoubler = ADF4351_Reg2->b.RMul2 + 1;     // 1 or 2
	Rcounter = ADF4351_Reg2->b.RCountVal;
	PFDFreq = (REFin * RefDoubler / RefD2) / Rcounter;

	OutputDivider = (1U<<ADF4351_Select_Output_Divider(RFout));

	
	if (ADF4351_Reg4->b.Feedback == 1) // fundamental
			N = ((RFout * OutputDivider) / PFDFreq);
	else										// divided
			N = (RFout / PFDFreq);

	INT = (uint16_t)N;
	MOD = (uint16_t)(round(/*1000 * */(PFDFreq / OutputChannelSpacing)));
	FRAC = (uint16_t)(round(((double)N - INT) * MOD));

	if (gcd)
	{
			D = gcd_iter((uint32_t)MOD, (uint32_t)FRAC);

			MOD = MOD / D;
			FRAC = FRAC / D;
	}

	if (MOD == 1)
			MOD = 2;

	*RFoutCalc = (((double)((double)INT + ((double)FRAC / (double)MOD)) * (double)PFDFreq / OutputDivider) * ((ADF4351_Reg4->b.Feedback == 1) ? 1 : OutputDivider));
	N = INT + (FRAC / MOD);

	/* Check for PFD Max error, return error code if not OK */
	if ((PFDFreq > ADF5451_PFD_MAX) && (ADF4351_Reg3->b.BandSelMode == 0)) return ADF4351_Err_PFD;
	if ((PFDFreq > ADF5451_PFD_MAX) && (ADF4351_Reg3->b.BandSelMode == 1) && (FRAC != 0)) return ADF4351_Err_PFD;
	if ((PFDFreq > 90) && (ADF4351_Reg3->b.BandSelMode == 1) && (FRAC != 0))  return ADF4351_Err_PFD;

//		Calculate Band Select Clock
		if (AutoBandSelectClock)
		{
				if (ADF4351_Reg3->b.BandSelMode == 0)   /// LOW
				{
					temp = (uint32_t)round(8 * PFDFreq);
					if ((8 * PFDFreq - temp) > 0)
					temp++;
					temp = (temp > 255) ? 255 : temp;
					BandSelectClockDivider = (double)temp;
				}
				else                                            // High
				{
					temp = (uint32_t)round(PFDFreq * 2);
					if ((2 * PFDFreq - temp) > 0)
						temp++;
					temp = (temp > 255) ? 255 : temp;
					BandSelectClockDivider = (double)temp;
				}
		}
		BandSelectClockFrequency = (PFDFreq / (uint32_t)BandSelectClockDivider);

		/* Check parameters */
		if (BandSelectClockFrequency > 500e3)  return ADF4351_Err_BandSelFreqTooHigh;  // 500kHz in fast mode
		if ((BandSelectClockFrequency > 125e3) & (ADF4351_Reg3->b.BandSelMode == 0))  return ADF4351_Err_BandSelFreqTooHigh;   // 125kHz in slow mode
		

		// So far so good, let's fill the registers
		
		ADF4351_Reg0->b.FracVal = (FRAC & 0x0fff);
		ADF4351_Reg0->b.IntVal = (INT & 0xffff);
		ADF4351_Reg1->b.ModVal = (MOD & 0x0fff);
		
		return ADF4351_Err_None;
}


/**
  *  \brief Returns current value from local register buffer
  * 	
  * @param  addr: 								Register address
  * @retval register value
  */
uint32_t ADF4351_GetRegisterBuf(int addr)
{
	return (addr<6) ? ADF4351_Reg[addr] : 0;
}



/**
  *  \brief Set R counter value
  * 	
  * @param  val: 								Counter value (1...1023)
  * @retval register value
  */
ADF4351_ERR_t ADF4351_SetRcounterVal(uint16_t val)
{
	if ((val>0) & (val<1024)) 
	{
		ADF4351_Reg2->b.RCountVal = val;
		return ADF4351_Err_None;
	}
	else 
		return ADF4351_Err_InvalidRCounterValue;
}






