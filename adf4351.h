/**
 * @file     adf4351.h
 * @brief    ADF4351 driver Header File
 * @version  V0.00
 * @date     18. January 2016
 *
 * @note
 *
 */

#ifndef _ADF4351_H_
#define _ADF4351_H_

#include "stm32f0xx.h"                  // Device header

/** \brief  Union type for the structure of Register0 in ADF4351
 */
typedef union
{
	struct
	{
		uint32_t ControlBits		:3;  		/*!< bit:  0.. 2 	CONTROL BITS */
		uint32_t FracVal				:12; 		/*!< bit:  3..14 	12-BIT FRACTIONAL VALUE (FRAC) */
		uint32_t IntVal					:16;  	/*!< bit: 15..30 	16- BIT INTEGER VALUE (INT) */
		uint32_t _reserved_0		:1;  		/*!< bit: 31     	RESERVED */
	} b;
	uint32_t w;
} PllRegister0_t;



/** \brief  Union type for the structure of Register1 in ADF4351
 */
typedef union
{
	struct
	{
		uint32_t ControlBits		:3;  		/*!< bit:  0.. 2 	CONTROL BITS */
		uint32_t ModVal					:12; 		/*!< bit:  3..14 	12-BIT MODULUS VALUE (MOD) */
		uint32_t PhaseVal				:12; 		/*!< bit: 15..26 	12-BIT PHASE VALUE (PHASE) */
		uint32_t Prescaler			:1; 		/*!< bit:  27		 	PRESCALER */
		uint32_t PhaseAdjust		:1; 		/*!< bit:  28		 	PHASE ADJUST */
		uint32_t _reserved_0		:3;  		/*!< bit: 29..31 	RESERVED */
	} b;
	uint32_t w;
} PllRegister1_t;


/** \brief  Union type for the structure of Register2 in ADF4351
 */
typedef union
{
	struct
	{
		uint32_t ControlBits		:3;  		/*!< bit:  0.. 2 	CONTROL BITS */
		uint32_t CounterReset		:1; 		/*!< bit:  3 		 	Counter Reset */
		uint32_t CPTristate 		:1; 		/*!< bit:  4 		 	Charge Pump Three-State */
		uint32_t PowerDown  		:1; 		/*!< bit:  5 		 	Power-Down */
		uint32_t PhasePolarity	:1; 		/*!< bit:  6 		 	Phase Detector Polarity */
		uint32_t LockPrecision	:1; 		/*!< bit:  7 		 	Lock Detect Precision */
		uint32_t LockFunction		:1; 		/*!< bit:  8 		 	Lock Detect Function */
		uint32_t CPCurrent			:12; 		/*!< bit:  9..12 	Charge Pump Current Setting */
		uint32_t DoubleBuffer		:1; 		/*!< bit:  13		 	Double Buffer */
		uint32_t RCountVal			:10; 		/*!< bit: 14..23 	10-Bit R Counter */
		uint32_t RDiv2 					:1; 		/*!< bit: 24		 	Double Buffer */
		uint32_t RMul2					:1; 		/*!< bit: 25		 	Double Buffer */
		uint32_t MuxOut					:3;  		/*!< bit: 26..28 	MUXOUT */		
		uint32_t LowNoiseSpur		:2; 		/*!< bit: 29..30	Low Noise and Low Spur Modes  */
		uint32_t _reserved_0		:1; 		/*!< bit: 31			RESERVED  */
	} b;
	uint32_t w;
} PllRegister2_t;



/** \brief  Union type for the structure of Register3 in ADF4351
 */
typedef union
{
	struct
	{
		uint32_t ControlBits		:3;  		/*!< bit:  0.. 2 	CONTROL BITS */
		uint32_t ClkDivVal			:12; 		/*!< bit:  3..14 	12-Bit Clock Divider Value */
		uint32_t ClkDivMod			:2; 		/*!< bit:  15..16 Clock Divider Mode */
		uint32_t _reserved_0		:1; 		/*!< bit:  17		 	RESERVED */
		uint32_t CsrEn 					:1; 		/*!< bit:  18		 	CSR Enable */
		uint32_t _reserved_1		:2; 		/*!< bit:  19..20	RESERVED */
		uint32_t ChargeCh				:1;			/*!< bit:  21     Charge Cancelation */
		uint32_t AntibacklashW	:1;			/*!< bit:  22     Antibacklash Pulse Width */
		uint32_t BandSelMode  	:1;			/*!< bit:  23     Band Select Clock Mode */
		uint32_t _reserved_2		:8; 		/*!< bit:  24..31	RESERVED */
	} b;
	uint32_t w;
} PllRegister3_t;


/** \brief  Union type for the structure of Register4 in ADF4351
 */
typedef union
{
	struct
	{
		uint32_t ControlBits	:3;  		/*!< bit:  0.. 2 	CONTROL BITS */
		uint32_t OutPower			:2;  		/*!< bit:  3.. 4 	Output Power */
		uint32_t OutEnable		:1;  		/*!< bit:  5 	RF Output Enable */
		uint32_t AuxPower			:2;  		/*!< bit:  6.. 7 	AUX Output Power */
		uint32_t AuxEnable		:1;  		/*!< bit:  8 	AUX Output Enable */
		uint32_t AuxSel				:1;  		/*!< bit:  9 	AUX Output Select */
		uint32_t Mtld					:1;  		/*!< bit: 10 	Mute Till Lock Detect (MTLD) */
		uint32_t VcoPowerDown	:1;  		/*!< bit: 11 	VCO Power-Down */
		uint32_t BandClkDiv		:8;  		/*!< bit: 12..19 	Band Select Clock Divider Value */
		uint32_t RfDivSel			:3;  		/*!< bit: 20..22 	RF Divider Select */
		uint32_t Feedback			:1;  		/*!< bit: 23 	 Feedback Select */
		uint32_t _reserved_0	:8;  		/*!< bit: 24..31 RESERVED */
	} b;
	uint32_t w;
} PllRegister4_t;


/** \brief  Union type for the structure of Register5 in ADF4351
 */
typedef union
{
	struct
	{
		uint32_t ControlBits		:3;  		/*!< bit:  0.. 2 	CONTROL BITS */
		uint32_t _reserved_0	  :16;  	/*!< bit:  3..18 RESERVED */
		uint32_t _reserved_1	  :2;  	  /*!< bit: 19..20 RESERVED */
		uint32_t _reserved_2	  :1;  	  /*!< bit: 21     RESERVED */
		uint32_t LdPinMode		  :2;  		/*!< bit: 22..23 LD Pin Mode */
		uint32_t _reserved_3  	:8;  		/*!< bit: 24..31 RESERVED */
	} b;
	uint32_t w;
} PllRegister5_t;





#endif

