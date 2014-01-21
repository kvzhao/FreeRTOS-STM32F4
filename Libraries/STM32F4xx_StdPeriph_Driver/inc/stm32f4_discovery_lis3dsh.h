/*
 * stm32f4_discovery_lis3dsh.h
 *
 *  Created on: Dec 26, 2013
 *      Author: Pawel
 *
 *      IsNo 2013
 *
 *      Akcelerometr MEMS zgodny z LIS3DSH
 *
 */

#ifndef STM32F4_DISCOVERY_LIS3DSH_H_
#define STM32F4_DISCOVERY_LIS3DSH_H_
//==========================================================================================================================

#include "stm32f4xx.h"
//#include "stm32f4xx_gpio.h"
//#include "stm32f4xx_rcc.h"
//#include "stm32f4xx_spi.h"

typedef unsigned char lis3dsh_register;
//-------------------------- struktura inicjalizacji ----------------------------------------------
typedef struct
{
	uint8_t OutputDataRate;
	uint8_t Axes_Enable;
	uint8_t BlockDataUpdate;
}LIS3DSH_InitTypeDef;

typedef struct
{
	short x;
	short y;
	short z;
}LIS3DSH_OutXYZTypeDef;

/* Maximum Timeout values for flags waiting loops. These timeouts are not based
 * on accurate values, they just guarantee that the application will not remain
 * stuck if the SPI communication is corrupted.
 * You may modify these timeout values depending on CPU frequency and application
 * conditions (interrupts routines ...).
*/
#define LIS3DSH_FLAG_TIMEOUT         ((uint32_t)0x1000)


//-------------------------- definicja pinów GPIO -------------------------------------------------
#define LIS3DSH_SPI							SPI1
#define LIS3DSH_SPI_CLK						RCC_APB2Periph_SPI1

#define LIS3DSH_SPI_SCK_PIN					GPIO_Pin_5					// PA.05
#define LIS3DSH_SPI_SCK_GPIO_PORT			GPIOA						// GPIOA
#define LIS3DSH_SPI_SCK_GPIO_CLK			RCC_AHB1Periph_GPIOA
#define LIS3DSH_SPI_SCK_SOURCE				GPIO_PinSource5
#define LIS3DSH_SPI_SCK_AF					GPIO_AF_SPI1

#define LIS3DSH_SPI_MISO_PIN				GPIO_Pin_6					// PA.6
#define LIS3DSH_SPI_MISO_GPIO_PORT			GPIOA						// GPIOA
#define LIS3DSH_SPI_MISO_GPIO_CLK			RCC_AHB1Periph_GPIOA
#define LIS3DSH_SPI_MISO_SOURCE				GPIO_PinSource6
#define LIS3DSH_SPI_MISO_AF					GPIO_AF_SPI1

#define LIS3DSH_SPI_MOSI_PIN				GPIO_Pin_7					// PA.7
#define LIS3DSH_SPI_MOSI_GPIO_PORT			GPIOA						// GPIOA
#define LIS3DSH_SPI_MOSI_GPIO_CLK			RCC_AHB1Periph_GPIOA
#define LIS3DSH_SPI_MOSI_SOURCE				GPIO_PinSource7
#define LIS3DSH_SPI_MOSI_AF					GPIO_AF_SPI1

#define LIS3DSH_SPI_CS_PIN					GPIO_Pin_3					// PE.03
#define LIS3DSH_SPI_CS_GPIO_PORT			GPIOE						// GPIOE
#define LIS3DSH_SPI_CS_GPIO_CLK				RCC_AHB1Periph_GPIOE

#define LIS3DSH_SPI_INT1_PIN				GPIO_Pin_0					// PE.00
#define LIS3DSH_SPI_INT1_GPIO_PORT			GPIOE						// GPIOE
#define LIS3DSH_SPI_INT1_GPIO_CLK			RCC_AHB1Periph_GPIOE
#define LIS3DSH_SPI_INT1_EXTI_LINE			EXTI_Line0
#define LIS3DSH_SPI_INT1_EXTI_PORT_SOURCE	EXTI_PortSourceGPIOE
#define LIS3DSH_SPI_INT1_EXTI_PIN_SOURCE	EXTI_PinSource0
#define LIS3DSH_SPI_INT1_EXTI_IRQn			EXTI0_IRQn

#define LIS3DSH_SPI_INT2_PIN				GPIO_Pin_1					// PE.01
#define LIS3DSH_SPI_INT2_GPIO_PORT			GPIOE						// GPIOE
#define LIS3DSH_SPI_INT2_GPIO_CLK			RCC_AHB1Periph_GPIOE
#define LIS3DSH_SPI_INT2_EXTI_LINE			EXTI_Line1
#define LIS3DSH_SPI_INT2_EXTI_PORT_SOURCE	EXTI_PortSourceGPIOE
#define LIS3DSH_SPI_INT2_EXTI_PIN_SOURCE	EXTI_PinSource1
#define LIS3DSH_SPI_INT2_EXTI_IRQn			EXTI1_IRQn

//-------------------------- definicje rejestrów LIS3DSH ------------------------------------------

/* Rejestr INFO1 -------------- Information register 1 --------------------------------------------
*	Default value: 0x21
*	Read only register
*/
#define LIS3DSH_INFO1_ADDR				0x0d

/* Rejestr INFO2 -------------- Information register 2 --------------------------------------------
*	Default value: 0x00
*	Read only register
*/
#define LIS3DSH_INFO2_ADDR				0x0e

/* Rejestr WHO_AM_I ----------- Who I am ID -------------------------------------------------------
*	Default value: 0x3f
*	Read only register
*/
#define LIS3DSH_WHO_AM_I_ADDR				0x0f
#define _I_AM_LIS3DSH						0X3f

/* Rejestr CTRL_REG3 ---------- Control Register 3 ------------------------------------------------
*	Default value: ---
*	Read/Write register
*
*		bit:
*			7:DR_EN		DRDY signal enable to INT1
*				Default value:0
*				0 = data ready signal not connected
*				1 = data ready signal connected to INT1
*			6:IEA		Interrupt signal polarity
*				Default value:0
*				0 = interrupt signals active LOW
*				1 = interrupt signals active HIGH
*			5:IEL		Interrupt signal latching
*				Default value:0
*				0 = interrupt signals latched
*				1 = interrupt signal pulsed
*			4:INT2_EN	Interrupt 2 enable/disable
*				Default value:0
*				0 = INT2 signal disabled
*				1 = INT2 signal enabled
* 			3:INT1_EN	Interrupt 1 enable/disable
* 				Default Value:0
* 				0 = INT1/DRDY signal disabled
* 				1 = INT1/DRDY signal enabled
* 			2:VFILT		Vector filter enable/disable
* 				Default value:0
* 				0 = vector filter disabled
* 				1 = vector filter enabled
* 			1:---
* 			0:STRT		Soft reset bit
* 				0 = no soft reset
* 				1 = soft reset (POR function)
*/
#define LIS3DSH_CTRL_REG3_ADDR				0x23
#define _LIS3DSH_DR_EN			7
#define _LIS3DSH_IEA			6
#define _LIS3DSH_IEL			5
#define _LIS3DSH_INT2_EN		4
#define _LIS3DSH_INT1_EN		3
#define _LIS3DSH_VFILT			2
#define _LIS3DSH_STRT			0

/*	Rejestr CTRL_REG4 --------- Control Register 4 ------------------------------------------------
*	Default value: ---
*	Read/Write register
*
*		bit:
*			7:ODR3		ODR[3:0]	Output data rate and power mode selection
*			6:ODR2
*			5:ODR1
*			4:ODR0
*				Default value:0000
*				ODR3	ODR2	ODR1	ODR0	ODR-selection
*				 0		 0		 0		 0		power down
*				 0		 0		 0		 1		3.125Hz
*				 0		 0		 1		 0		6.25Hz
*				 0		 0		 1		 1		12.5Hz
*				 0		 1		 0		 0		25Hz
*				 0		 1		 0		 1		50Hz
*				 0		 1		 1		 0		100Hz
*				 0		 1		 1		 1		400Hz
*				 1		 0		 0		 0		800Hz
*				 1		 0		 0		 1		1600Hz
*			3:BDU		Block data update
*				Default value:0
*				0:continuos update
*				1:output registers not updated (until MSB and LSB reading)
*			2:ZEN		Z axis enable
*				Default value:1
*				0:Z axis disabled
*				1:Z axis enabled
*			1:YEN		Y axis enable
*				Default value:1
*				0:Y axis disabled
*				1:Y axis enabled
*			0:XEN		X axis enable
*				Default value:1
*				0=X axis disabled
*				1=X axis enabled
*
*/
#define LIS3DSH_CTRL_REG4_ADDR				0x20
#define _LIS3DSH_ODR3					7
#define _LIS3DSH_ODR2					6
#define _LIS3DSH_ODR1					5
#define _LIS3DSH_ODR0					4
#define _LIS3DSH_BDU					3
#define _LIS3DSH_Z_ENABLE				2
#define _LIS3DSH_YENABLE				1
#define _LIS3DSH_XENABLE				0
#define LIS3DSH_ODR_POWER_DOWN			((uint8_t)0b00000000)
#define LIS3DSH_ODR_3_125_HZ			((uint8_t)0b00010000)
#define LIS3DSH_ODR_6_25_HZ				((uint8_t)0b00100000)
#define LIS3DSH_ODR_12_5_HZ				((uint8_t)0b00110000)
#define LIS3DSH_ODR_25_HZ				((uint8_t)0b01000000)
#define LIS3DSH_ODR_50_HZ				((uint8_t)0b01010000)
#define LIS3DSH_ODR_100_HZ				((uint8_t)0b01100000)
#define LIS3DSH_ODR_400_HZ				((uint8_t)0b01110000)
#define LIS3DSH_ODR_800_HZ				((uint8_t)0b10000000)
#define LIS3DSH_ODR_1600_HZ				((uint8_t)0b10010000)
#define LIS3DSH_XYZ_ENABLE				((uint8_t)0b00000111)
#define LIS3DSH_BDU_CONTINOUS_UPDATE	((uint8_t)0b00000000)
#define LIS3DSH_BDU_NOT_UPDATET			((uint8_t)0b00001000)
/* Rejestr CTRL_REG5 ---------- Control Register 5 ------------------------------------------------
*	Default value: ---
*	Read/Write register
*
*		bit:
*			7:BW2		Anti-aliasing filter bandwidth
*			6:BW1
*				Default value: 00
*				BW2		BW1		BW-selection
*				 0		 0			800 Hz
*				 0		 1			400 Hz
*				 1		 0			200 Hz
*				 1		 1			50 Hz
*			5:FSCALE2	Full-scale selection
*			4:FSCALE1
*			3:FSCALE0
*				Default value: 000
*				FSCALE2	FSCALE1	FSCALE0 FSCALE-selection
*					0		0		0		+/- 2G
*					0		0		1		+/- 4G
*					0		1		0		+/- 6G
*					0		1		1		+/- 8G
*					1		0		0		+/- 16G
*
*			2:ST2		Self-test enable
*			1:ST1
*				Default value: 00
*				ST2		ST1		self-test mode
*				 0		 0		self-test disabled
*				 0		 1		Positive sign self-test
*				 1		 0		Negative sign self-test
*				 1		 1		Not allowed
*			0:SIM		SPI serial interface mode selection
*				Default value: 0
*				0:	4-wire interface
*				1:	3-wire interface
*
*/
#define LIS3DSH_CTRL_REG5_ADDR				0x24
#define _LIS3DSH_BW2						7
#define _LIS3DSH_BW1						6
#define _LIS3DSH_FSCALE2					5
#define _LIS3DSH_FSCALE1					4
#define _LIS3DSH_FSCALE0					3
#define _LIS3DSH_ST2						2
#define _LIS3DSH_ST1						1
#define _LIS3DSH_SIM						0

/* Rejestr CTRL_REG6 ---------- Control Register 6 ------------------------------------------------
*	Default value: ---
*	Read/Write register
*
*		bit:
*			7:BOOT			Force reboot, cleared as soon as the reboot is finished
*				Active: 1
*			6:FIFO_EN		FIFO enable
*				Default value 0
*				0:disable
*				1:enable
*			5:WTM_EN		Enable FIFO Watermark level use
*				Default value: 0
*				0:disable
*				1:enable
*			4:ADD_INC		Register address automatically incremented during a multiple byte access
*							with a serial interface (I2C or SPI)
*				0:disable
*				1:enable
*			3:P1_EMPTY		Enable FIFO Empty indication on int1
*				Default value 0
*				0:disable
*				1:enable
*			2:P1_WTM		FIFO Watermark interrupt on int1
*				Default value 0
*				0:disable
*				1:enable
*			1:P1_OVER_RUN	FIFO overrun interrupt on int1
*				Default value 0
*				0:disable
*				1:enable
*			0:P2_BOOT		BOOT interrupt on int2
*				Default value 0
*				0:disable
*				1:enable
*/
#define LIS3DSH_CTRL_REG6_ADDR				0x25
#define _LIS3DSH_BOOT			7
#define _LIS3DSH_FIFO_EN		6
#define _LIS3DSH_WTM_EN			5
#define _LIS3DSH_ADD_INC		4
#define _LIS3DSH_P1_EMPTY		3
#define _LIS3DSH_P1_WTM			2
#define _LIS3DSH_P1_OVER_RUN	1
#define _LIS3DSH_P2_BOOT		0

/*	Rejestr STATUS ------------- Status Data Register ---------------------------------------------
*	Default value: ---
*	Read only register
*
*		bit:
*			7:ZYXOR		X, Y, and Z axis data overrun
*				Default value: 0
*				0: no overrun has occurred
*				1: a new set of data has overwritten the previous ones
*			6:ZOR		Z axis data overrun
*				Default value: 0
*				0: no overrun has occurred
*				1: a new data for the Z-axis has overwritten the previous one
*			5:YOR		Y axis data overrun
*				Default value: 0
*				0: no overrun has occurred
*				1: a new data for the Y-axis has overwritten the previous one
*			4:XOR		X axis data overrun
*				Default value: 0
*				0: no overrun has occurred
*				1: a new data for the X-axis has overwritten the previous one
*			3:ZYXDA		X, Y, and Z axis new data available
*				Default value: 0
*				0: a new set of data is not yet available
*				1: a new set of data is available
*			2:ZDA		Z axis new data available
*				Default value: 0
*				0: a new data for the Z-axis is not yet available
*				1: a new data for the Z-axis is available
*			1:YDA		Y axis new data available
*				Default value: 0
*				0: a new data for the Y-axis is not yet available
*				1: a new data for the Y-axis is available
*			0:XDA		X axis new data available
*				Default value: 0
*				0: a new data for the X-axis is not yet available
*				1: a new data for the X-axis is available
*/
#define LIS3DSH_STATUS_ADDR					0x27
#define _LIS3DSH_ZYXOR			7
#define _LIS3DSH_ZOR			6
#define _LIS3DSH_YOR			5
#define _LIS3DSH_XOR			4
#define _LIS3DSH_ZYXDA			3
#define _LIS3DSH_ZDA			2
#define _LIS3DSH_YDA			1
#define _LIS3DSH_XDA			0

/*	Rejestr OUT_T ------------- Temperature Output ------------------------------------------------
*	Default value: ---
*	Read only register
*
*	Temperature output register.
*	Temperature data (1LSB/deg - 8-bit resolution).
*	The value is expressed as two's complement.
*
*/
#define LIS3DSH_OUT_T_ADDR					0x0c

/*	Rejestr OFFSET_X ---------- X-axis offset correction ------------------------------------------
*	Default value: 0
*	Read/Write register
*
*	Offset correction X-axis register,signed value.
*/
#define LIS3DSH_OFFSET_X_ADDR				0x10

/*	Rejestr OFFSET_Y ---------- Y-axis offset correction ------------------------------------------
*	Default value: 0
*	 Read Write register
*
*	 Offset correction Y-axis register, signed value.
*/
#define LIS3DSH_OFFSET_Y_ADDR				0x11

/*	Rejestr OFFSET_Z ---------- Z-axis offset correction ------------------------------------------
*	Default value: 0
*	Read/Write register
*
*	Offset correction Z-axis register, signed value.
*/
#define LIS3DSH_OFFSET_Z_ADDR				0x12

/*	Rejestr CS_X -------------- Constant shift X --------------------------------------------------
*	Default value: 0
*	Read/Write register
*
*	Constant shift signed value X-axis register - state machine only.
*/
#define LIS3DSH_CS_X_ADDR					0x13

/*	Rejestr CS_Y -------------- Constant shift Y --------------------------------------------------
*	Default value: 0
*	Read/Write register
*
*	Constant shift signed value Y-axis register - state machine only
*/
#define LIS3DSH_CS_Y_ADDR					0x14

/*	Rejestr CS_Z -------------- Constant shift Z --------------------------------------------------
*	Default value: 0
*	Read/Write register
*
*	Constant shift signed value Y-axis register - state machine only.
*/
#define LIS3DSH_CS_Z_ADDR					0x15

/*	Rejestr LC ---------------- Long counter registers --------------------------------------------
*	Default value: 1
*	Read/Write register
*
*	16-bit long-counter register for interrupt state machine programs timing.
*	01h=counting stopped, 00h=counter full: interrupt available and counter is set to default.
*	Values higher than 00h:counting
*/
#define LIS3DSH_LC_H_ADDR					0x16
#define LIS3DSH_LC_L_ADDR					0x17

/*	Rejestr STAT -------------- Interrupt status - interrupt synchronization register -------------
*	Default value: ---
*	Read only register
*
*		bit:
*			7:LONG		interrupt flag common for both SM
*				0: no interrupt
*				1: long counter (LC)
*			6:SYNCW		Synchronization for external Host Controller interrupt based on output data
*				0: no action waiting from host
*				1: action from host based on output data
*			5:SYNC1
*				0: SM1 running normally
*				1: SM1 stopped and await restart request from SM2
*			4:SYNC2
*				0: SM2 running normally
*				1: SM2 stopped and await restart request from SM1
*			3:INT_SM1	SM1 - Interrupt Selection
*				0: SM1 interrupt disable
*				1: SM1 interrupt enable
*			2:INT_SM2	SM2 - Interrupt Selection
*				0: SM2 interrupt disable
*				1: SM2 interrupt enable
*			1:DOR		Data overrun indicates not read data from output register when
*						next data samples measure start
*				0: no overrun
*				1: data overrun data overrun bit is reset when next
sample is ready
*			0:DRDY
*/
#define LIS3DSH_STAT_ADDR					0x18
#define _LIS3DSH_LONG			7
#define _LIS3DSH_SYNCW			6
#define _LIS3DSH_SYNC1			5
#define _LIS3DSH_SYNC2			4
#define _LIS3DSH_INT_SM1		3
#define _LIS3DSH_INT_SM2		2
#define _LIS3DSH_DOR			1
#define _LIS3DSH_DRDY			0

/*	Rejestr VFC_1 ------------- Vector filter coefficient 1 ---------------------------------------
*	Default value: 0
*	Read/Write register
*
*	Vector coefficient register 1 for DIff filter.
*/
#define LIS3DSH_VFC_1_ADDR					0x1b

/*	Rejestr VFC_2 ------------- Vector filter coefficient 2 ---------------------------------------
*	Default value: 0
*	Read/Write register
*
*	Vector coefficient register 2 for DIff filter.
*/
#define LIS3DSH_VFC_2_ADDR					0x1c

/*	Rejestr VFC_3 ------------- Vector filter coefficient 3 ---------------------------------------
*	Default value: 0
*	Read/Write register
*
*	Vector coefficient register 3 for FSM2 filter.
*/
#define LIS3DSH_VFC_3_ADDR					0x1d

/*	Rejestr VFC_4 ------------- Vector filter coefficient 4 ---------------------------------------
*	Default value: 0
*	Read/Write register
*
*	Vector coefficient register 4 for DIff filter.
*/
#define LIS3DSH_VFC_4_ADDR					0x1e

/*	Rejestr THRS3 ------------ Threshold value 3 --------------------------------------------------
*	Default value: 0
*	Read/Write register
*
*	Threshold value register.
*/
#define LIS3DSH_THRS3_ADDR					0x1f

/*	Rejestr OUT_X ------------ Output register X --------------------------------------------------
*	Default value: 0
*	Read only register
*
*	X-axis output register.
*/
#define LIS3DSH_OUT_X_L_ADDR				0x28
#define LIS3DSH_OUT_X_H_ADDR				0x29

/*	Rejestr OUT_Y ------------ Output register Y --------------------------------------------------
*	Default value: 0
*	Read only register
*
*	Y-axis output register.
*/
#define LIS3DSH_OUT_Y_L_ADDR				0x2a
#define LIS3DSH_OUT_Y_H_ADDR				0x2b

/*	Rejestr OUT_Z ------------ Output register Z --------------------------------------------------
*	Default value: 0
*	Read only register
*
*	Z-axis output register.
*/
#define LIS3DSH_OUT_Z_L_ADDR				0x2c
#define LIS3DSH_OUT_Z_H_ADDR				0x2d

/*	Rejestr FIFO_CTRL -------- FIFO control register ----------------------------------------------
*	Default value: ---
*	Read/write register
*
*		bit:
*			7:FMODE2	FMODE[2:0] FIFO Mode Selection.
*			6:FMODE1
*			5:FMODE0
*				FMODE2	FMODE1	FMODE0	MODE
*					0		0		0	Bypass Mode. FIFO turned off
*					0		0		1	FIFO Mode. Stop collecting data when FIFO is full.
*					0		1		0	Stream Mode. If the FIFO is full the new sample
*										overwrites the older one
*					0		1		1	Stream mode until trigger is deasserted, then FIFO mode
*					1		0		0	Bypass mode until trigger is deasserted, then Stream mode
*					1		0		1	Not Used.
*					1		1		0	Not Used.
*					1		1		1	Bypass mode until trigger is deasserted, then FIFO mode
*			4:WTMP4		WTMP[4:0] - FIFO Watermark pointer; FIFO deep if the Watermark is enabled.
*			3:WTMP3
*			2:WTMP2
*			1:WTMP1
*			0:WTMP0
*/
#define LIS3DSH_FIFO_CTRL_ADDR				0x2e
#define _LIS3DSH_FMODE2		7
#define _LIS3DSH_FMODE1		6
#define _LIS3DSH_FMODE0		5
#define _LIS3DSH_WTMP4		4
#define _LIS3DSH_WTMP3		3
#define _LIS3DSH_WTMP2		2
#define _LIS3DSH_WTMP1		1
#define _LIS3DSH_WTMP0		0

/*	Rejestr FIFO_SRC --------- FIFO SRC control register ------------------------------------------
*	Default value: ---
*	Read only register
*
*		bit:
*			7:WTM		Watermark status.
*				0: FIFO filling is lower than WTM level
*				1: FIFO filling is equal or higher than WTM level
*			6:OVRN FIFO	Overrun bit status
*				0: FIFO is not completely filled
*				1: FIFO is completely filled
*			5:EMPTY		FIFO empty bit
*				0: FIFO not empty
*				1: FIFO empty)
*			4:FSS4		FSS[4:0] FIFO stored data level
*			3:FSS3
*			2:FSS2
*			1:FSS1
*			0:FSS0
*/
#define LIS3DSH_FIFO_SRC_ADDR				0x2f
#define _LIS3DSH_WTM		7
#define _LIS3DSH_OVRN		6
#define _LIS3DSH_EMPTY		5
#define _LIS3DSH_FSS4		4
#define _LIS3DSH_FSS3		3
#define _LIS3DSH_FSS2		2
#define _LIS3DSH_FSS1		1
#define _LIS3DSH_FSS0		0

/*	Rejestr CTRL_REG1 -------- SM1 control register -----------------------------------------------
*	Default value: 0
*	Read/write register
*
*		bit:
*			7:HYST2_1		Hysteresis unsigned value to be added
*							or subtracted from threshold value in SM1
*			6:HYST1_1
*			5:HYST0_1
*				Default value: 000
*			4: -
*			3:SM1_PIN
*				Default value:0
*				0: SM1 interrupt routed to INT1
*				1: SM1 interrupt routed to INT2 pin
*			2: -
*			1: -
*			0:SM1_EN
*				Default value: 0
*				0: SM1 disabled
*				1: SM1 enabled
*/
#define LIS3DSH_CTRL_REG1_ADDR				0x21
#define _LIS3DSH_HYST2_1		7
#define _LIS3DSH_HYST1_1		6
#define _LIS3DSH_HYST0_1		5
#define _LIS3DSH_SM1_PIN		3
#define _LIS3DSH_SM1_EN			0

/*	Rejestrs ST1_1-ST1_16 ---- SM1 code registers [1-16] ------------------------------------------
*	Default value: ---
*	Write only registers
*
*	State machine 1 system register is made up of 16, 8- bit registers
*	to implement 16-step op-code.
*/
#define LIS3DSH_ST1_1_ADDR					0x40
#define LIS3DSH_ST1_2_ADDR					0x41
#define LIS3DSH_ST1_3_ADDR					0x42
#define LIS3DSH_ST1_4_ADDR					0x43
#define LIS3DSH_ST1_5_ADDR					0x44
#define LIS3DSH_ST1_6_ADDR					0x45
#define LIS3DSH_ST1_7_ADDR					0x46
#define LIS3DSH_ST1_8_ADDR					0x47
#define LIS3DSH_ST1_9_ADDR					0x48
#define LIS3DSH_ST1_10_ADDR					0x49
#define LIS3DSH_ST1_11_ADDR					0x4a
#define LIS3DSH_ST1_12_ADDR					0x4b
#define LIS3DSH_ST1_13_ADDR					0x4c
#define LIS3DSH_ST1_14_ADDR					0x4d
#define LIS3DSH_ST1_15_ADDR					0x4e
#define LIS3DSH_ST1_16_ADDR					0x4f

/*	Rejestr TIM4_1 ----------- SM1 general timer --------------------------------------------------
*	Default value: ---
*	Write only register
*
*	8-bit general timer (unsigned value) for SM1 operation timing.
*/
#define LIS3DSH_TIM4_1_ADDR					0x50

/*	Rejestr TIM3_1 ----------- SM1 general timer --------------------------------------------------
*	Default value: ---
*	Write only register
*
*	8-bit general timer (unsigned value) for SM1 operation timing.
*/
#define LIS3DSH_TIM3_1_ADDR					0x51

/*	Rejestr TIM2_1 ----------- SM1 general timer --------------------------------------------------
*	Default value: ---
*	Write only register
*
*	16-bit general timer (unsigned value) for SM1 operation timing.
*/
#define LIS3DSH_TIM2_1_L_ADDR				0x52
#define LIS3DSH_TIM2_1_H_ADDR				0x53

/*Rejestr TIM1_1 ------------- SM1 general timer --------------------------------------------------
*	Default value: ---
*	Write only register
*
*	16-bit general timer (unsigned value) for SM1 operation timing.
*/
#define LIS3DSH_TIM1_1_L_ADDR				0x54
#define LIS3DSH_TIM1_1_H_ADDR				0x55

/*	Rejestr THRS2_1 ---------- SM1 threshold value 1 ----------------------------------------------
*	Default value: ---
*	Write only register
*
*	Threshold value for SM1 operation.
*/
#define LIS3DSH_THRS2_1_ADDR				0x56

/*	Rejestr THRS1_1 ---------- SM1 threshold value 2 ----------------------------------------------
*	Default value: ---
*	Write only register
*
*	Threshold value for SM1 operation.
*/
#define LIS3DSH_THRS1_1_ADDR				0x57

/*	Rejestr MASK1_B ---------- SM1 axis and sign mask ---------------------------------------------
*	Default value: ---
*	Write only register
*
*	Axis and sign mask (swap) for SM1 motion detection operation.
*
*		bit:
*			7:P_X
*				0: X + disabled
*				1: X + enabled
*			6:N_X
*				0: X - disabled
*				1: X – enabled
*			5:P_Y
*				0: X + disabled
*				1: X + enabled
*			4:N_Y
*				0: X - disabled
*				1: X – enabled
*			3:P_Z
*				0: X + disabled
*				1: X + enabled
*			2:N_Z
*				0: X - disabled
*				1: X – enabled
*			1:P_V
*				0: X + disabled
*				1: X + enabled
*			0:N_V
*				0: X - disabled
*				1: X – enabled
*/
#define LIS3DSH_MASK1_B_ADDR				0x59
#define _LIS3DSH_P_X		7
#define _LIS3DSH_N_X		6
#define _LIS3DSH_P_Y		5
#define _LIS3DSH_N_Y		4
#define _LIS3DSH_P_Z		3
#define _LIS3DSH_N_Z		2
#define _LIS3DSH_P_V		1
#define _LIS3DSH_N_V		0

/*	Rejestr MASK1_A ---------- SM1 axis and sign mask ---------------------------------------------
*	Default value: ---
*	Write only register
*
*	Axis and sign mask (default) for SM1 motion detection operation.
*
*		bit:
*			7:P_X
*				0: X + disabled
*				1: X + enabled
*			6:N_X
*				0: X - disabled
*				1: X – enabled
*			5:P_Y
*				0: X + disabled
*				1: X + enabled
*			4:N_Y
*				0: X - disabled
*				1: X – enabled
*			3:P_Z
*				0: X + disabled
*				1: X + enabled
*			2:N_Z
*				0: X - disabled
*				1: X – enabled
*			1:P_V
*				0: X + disabled
*				1: X + enabled
*			0:N_V
*				0: X - disabled
*				1: X – enabled
*/
#define LIS3DSH_MASK1_A_ADDR				0x5a
#define _LIS3DSH_P_X		7
#define _LIS3DSH_N_X		6
#define _LIS3DSH_P_Y		5
#define _LIS3DSH_N_Y		4
#define _LIS3DSH_P_Z		3
#define _LIS3DSH_N_Z		2
#define _LIS3DSH_P_V		1
#define _LIS3DSH_N_V		0

/*	Rejestr SETT1 ------------ SM1 detection settings ---------------------------------------------
*	Default value: ---
*	Write only register
*
*	Setting of threshold, peak detection and flags for SM1 motion detection operation.
*
*		bit:
*			7:P_DET		SM1 peak detection
*				Default value:0
*				0: peak detection disabled
*				1: peak detection enabled
*			6:THR3_SA
*				Default value:0
*				0: no action
*				1: threshold 3 limit value for axis and sign mask reset (MASKB_1)
*			5:ABS
*				Default value:0
*				0: unsigned thresholds
*				1: signed thresholds
*			4:-
*			3:-
*			2:THR3_MA
*				Default value:0
*				0: no action
*				1: threshold 3 limit value for axis and sign mask reset (MASKA_1)
*			1:R_TAM		Next condition validation flag
*				Default value:0
*				0: no valid next condition found
*				1: valid next condition found and reset
*			0:SITR
*				Default value:0
*				0: no actions
*				1: program flow can be modified by STOP and CONT commands
*/
#define LIS3DSH_SETT1_ADDR					0x5b
#define _LIS3DSH_P_DET		7
#define _LIS3DSH_THR3_SA	6
#define _LIS3DSH_ABS		5
#define _LIS3DSH_THR3_MA	2
#define _LIS3DSH_R_TAM		1
#define _LIS3DSH_SITR		0

/*	Rejestr PR1 -------------- Program-reset pointer ----------------------------------------------
*	Default value: ---
*	Read only register
*
*	Program and reset pointer for SM1 motion detection operation.
*
*		bit:
*			7:PP3		PP[3:0] SM1 program pointer address
*			6:PP2
*			5:PP1
*			4:PP0
*			3:PR3		PR[3:0] SM1 reset pointer address
*			2:PR2
*			1:PR1
*			0:PR0
*/
#define LIS3DSH_RP1_ADDR					0x5c
#define _LIS3DSH_PP3		7
#define _LIS3DSH_PP2		6
#define _LIS3DSH_PP1		5
#define _LIS3DSH_PP0		4
#define _LIS3DSH_PR3		3
#define _LIS3DSH_PR2		2
#define _LIS3DSH_PR1		1
#define _LIS3DSH_PR0		0

/*	Rejestr TC1 -------------- Timer counter ------------------------------------------------------
*	Default value: ---
*	Read only registers
*
*	16-bit general timer (unsigned output value) for SM1 operation timing.
*/
#define LIS3DSH_TC1_L_ADDR					0x5d
#define LIS3DSH_TC1_H_ADDR					0x5e

/*	Rejestr OUTS1 ------------ Main set flag ------------------------------------------------------
*	Default value: ---
*	Read only register
*
*	Output flags on axis for interrupt SM1 management.
*
*		bit:
*			7:P_X
*				0: X + no show
*				1: X + show
*			6:N_X
*				0: X - no show
*				1: X - show
*			5:P_Y
*				0: X + no show
*				1: X + show
*			4:N_Y
*				0: X - no show
*				1: X - show
*			3:P_Z
*				0: X + no show
*				1: X + show
*			2:N_Z
*				0: X - no show
*				1: X - show
*			1:P_V
*				0: X + no show
*				1: X + show
*			0:N_V
*				0: X - no show
*				1: X - show
*/
#define LIS3DSH_OUTS1_ADDR					0x5f
#define _LIS3DSH_P_X		7
#define _LIS3DSH_N_X		6
#define _LIS3DSH_P_Y		5
#define _LIS3DSH_N_Y		4
#define _LIS3DSH_P_Z		3
#define _LIS3DSH_N_Z		2
#define _LIS3DSH_P_V		1
#define _LIS3DSH_N_V		0

/*	Rejestr PEAK1 ------------ Peak value ---------------------------------------------------------
*	Default value: ---
*	Read only register
*
*	Peak detection value register for SM1 operation.
*/
#define LIS3DSH_PEAK1_ADDR					0x19

/*	Rejestr CTRL_REG2 -------- SM2 control register -----------------------------------------------
*	Default value: ---
*	Read/write register
*
*	State program 2 interrupt MNG - SM2 control register.
*
*		bit:
*			7:HYST2_2		HYST2_2:HYST0_2 Hysteresis unsigned value to be added
*							or subtracted from threshold value in SM2.
*			6:HYST1_2
*			5:HYST0_2
*				Default value: 000
*			4:-
*			3:SM2_PIN
*				Default value: 0
*				0: SM2 interrupt routed to INT1
*				1: SM2 interrupt routed to INT1 pin.
*			2:-
*			1:-
*			0:SM2_EN
*				Default value: 0
*				0: SM2 disabled
*				1: SM2 enabled
*/
#define LIS3DSH_CTRL_REG2_ADDR				0x22
#define _LIS3DSH_HYST2_2		7
#define _LIS3DSH_HYST1_2		6
#define _LIS3DSH_HYST0_2		5
#define _LIS3DSH_SM2_PIN		3
#define _LIS3DSH_SM2_EN			0

/*	Rejestrs ST2_1-ST2_16 ---- SM2 code registers [1-16] ------------------------------------------
*	Default value: ---
*	Write only registers
*
*	State machine 2 system register is made up of 16 8-bit registers,
*	to implement 16-step op-code.
*/
#define LIS3DSH_ST2_1_ADDR					0x60
#define LIS3DSH_ST2_2_ADDR					0x61
#define LIS3DSH_ST2_3_ADDR					0x62
#define LIS3DSH_ST2_4_ADDR					0x63
#define LIS3DSH_ST2_5_ADDR					0x64
#define LIS3DSH_ST2_6_ADDR					0x65
#define LIS3DSH_ST2_7_ADDR					0x66
#define LIS3DSH_ST2_8_ADDR					0x67
#define LIS3DSH_ST2_9_ADDR					0x68
#define LIS3DSH_ST2_10_ADDR					0x69
#define LIS3DSH_ST2_11_ADDR					0x6a
#define LIS3DSH_ST2_12_ADDR					0x6b
#define LIS3DSH_ST2_13_ADDR					0x6c
#define LIS3DSH_ST2_14_ADDR					0x6d
#define LIS3DSH_ST2_15_ADDR					0x6e
#define LIS3DSH_ST2_16_ADDR					0x6f

/*	Rejestr TIM4_2 ----------- SM2 general timer --------------------------------------------------
*	Default value: ---
*	Write only register
*
*	8-bit general timer (unsigned value) for SM2 operation timing.
*/
#define LIS3DSH_TIM4_2_ADDR					0x70

/*	Rejestr TIM3_2 ----------- SM2 general timer --------------------------------------------------
*	Default value: ---
*	Write only register
*
*	8-bit general timer (unsigned value) for SM2 operation timing.
*/
#define LIS3DSH_TIM3_2_ADDR					0x71

/*	Rejestr TIM2_2 ----------- SM2 general timer --------------------------------------------------
*	Default value: ---
*	Write only register
*
*	16-bit general timer (unsigned value) for SM2 operation timing.
*/
#define LIS3DSH_TIM2_2_L_ADDR				0x72
#define LIS3DSH_TIM2_2_H_ADDR				0x73

/*	Rejestr TIM1_2 ----------- SM2 general timer --------------------------------------------------
*	Default value: ---
*	Write only register
*
*	16-bit general timer (unsigned value) for SM2 operation timing.
*/
#define LIS3DSH_TIM1_2_L_ADDR				0x74
#define LIS3DSH_TIM1_2_H_ADDR				0x75

/*	Rejestr THRS2_2 ---------- SM2 threshold value 1 ----------------------------------------------
*	Default value: ---
*	Write only register
*
*	Threshold signed value for SM2 operation.
*/
#define LIS3DSH_THRS2_2_ADDR				0x76

/*	Rejestr THRS1_2 ---------- SM2 threshold value 2 ----------------------------------------------
*	Default value: ---
*	Write only register
*
*	Threshold signed value for SM2 operation.
*/
#define LIS3DSH_THRS1_2_ADDR				0x77

/*Rejestr MASK2_B ------------ SM2 axis and sign mask ---------------------------------------------
*	Default value: ---
*	Write only register
*
*	Axis and sign mask (swap) for SM2 motion detection operation.
*
*		bit:
*			7:P_X
*				0: X + disabled
*				1: X + enabled
*			6:N_X
*				0: X - disabled
*				1: X – enabled
*			5:P_Y
*				0: X + disabled
*				1: X + enabled
*			4:N_Y
*				0: X - disabled
*				1: X – enabled
*			3:P_Z
*				0: X + disabled
*				1: X + enabled
*			2:N_Z
*				0: X - disabled
*				1: X – enabled
*			1:P_V
*				0: X + disabled
*				1: X + enabled
*			0:N_V
*				0: X - disabled
*				1: X – enabled
*/
#define LIS3DSH_MASK2_B_ADDR				0x79
#define _LIS3DSH_P_X		7
#define _LIS3DSH_N_X		6
#define _LIS3DSH_P_Y		5
#define _LIS3DSH_N_Y		4
#define _LIS3DSH_P_Z		3
#define _LIS3DSH_N_Z		2
#define _LIS3DSH_P_V		1
#define _LIS3DSH_N_V		0

/*	Rejestr MASK2_A ---------- SM2 axis and sign mask ---------------------------------------------
*	Default value: ---
*	Write only register
*
*	Axis and sign mask (default) for SM2 motion detection operation.
*
*		bit:
*			7:P_X
*				0: X + disabled
*				1: X + enabled
*			6:N_X
*				0: X - disabled
*				1: X – enabled
*			5:P_Y
*				0: X + disabled
*				1: X + enabled
*			4:N_Y
*				0: X - disabled
*				1: X – enabled
*			3:P_Z
*				0: X + disabled
*				1: X + enabled
*			2:N_Z
*				0: X - disabled
*				1: X – enabled
*			1:P_V
*				0: X + disabled
*				1: X + enabled
*			0:N_V
*				0: X - disabled
*				1: X – enabled
*/
#define LIS3DSH_MASK2_A_ADDR				0x7a
#define _LIS3DSH_P_X		7
#define _LIS3DSH_N_X		6
#define _LIS3DSH_P_Y		5
#define _LIS3DSH_N_Y		4
#define _LIS3DSH_P_Z		3
#define _LIS3DSH_N_Z		2
#define _LIS3DSH_P_V		1
#define _LIS3DSH_N_V		0

/*	Rejestr SETT2 ------------ SM2 detection settings ---------------------------------------------
*	Default value: ---
*	Write only register
*
*	Setting of threshold, peak detection and flags for SM2 motion detection operation.
*
*		bit:
*			7:P_DET			SM2 peak detection
*				Default value: 0
*				0: peak detection disabled
*				1: peak detection enabled
*			6:THR3_SA
*				Default value: 0
*				0: no action
*				1: threshold 3 limit value for axis and sign mask reset (MASK2_B)
*			5:ABS
*				Default value: 0
*				0: unsigned thresholds
*				1: signed thresholds
*			4:-
*			3:-
*			2:THR3_MA
*				Default value: 0
*				0: no action
*				1: threshold 3 limit value for axis and sign mask reset (MASK2_A)
*			1:RTAM			Next condition validation flag
*				Default value: 0
*				0: no valid next condition found
*				1: valid next condition found and reset
*			0:SITR
*				Default value: 0
*				0: no actions
*				1: program flow can be modified by STOP and CONT commands
*/
#define LIS3DSH_SETT2_ADDR					0x7b
#define _LIS3DSH_P_DET		7
#define _LIS3DSH_THR3_SA	6
#define _LIS3DSH_ABS		5
#define _LIS3DSH_THR3_MA	2
#define _LIS3DSH_RTAM		1
#define _LIS3DSH_SITR		0

/*	Rejestr PR2 -------------- Program-reset pointer ----------------------------------------------
*	Default value: ---
*	Read only register
*
*	Program and reset pointer for SM2 motion detection operation.
*
*		bit:
*			7:PP3		PP[3:0] SM2 program pointer address
*			6:PP2
*			5:PP1
*			4:PP0
*			3:PR3		PR[3:0] SM2 reset pointer address
*			2:PR2
*			1:PR1
*			0:PR0
*/
#define LIS3DSH_RP2_ADDR					0x7c
#define _LIS3DSH_PP3		7
#define _LIS3DSH_PP2		6
#define _LIS3DSH_PP1		5
#define _LIS3DSH_PP0		4
#define _LIS3DSH_PR3		3
#define _LIS3DSH_PR2		2
#define _LIS3DSH_PR1		1
#define _LIS3DSH_PR0		0

/*	Rejestr TC2 -------------- Timer counter ------------------------------------------------------
*	Default value: ---
*	Read only registers
*
*	16-bit general timer (unsigned output value) for SM2 operation timing.
*/
#define LIS3DSH_TC2_L_ADDR					0x7d
#define LIS3DSH_TC2_H_ADDR					0x7e

/*	Rejestr OUTS2 ------------ Main set flag ------------------------------------------------------
*	Default value: ---
*	Read only register
*
*	Output flags on axis for interrupt SM2 management.
*
*		bit:
*			7:P_X
*				0: X + no show
*				1: X + show
*			6:N_X
*				0: X - no show
*				1: X - show
*			5:P_Y
*				0: X + no show
*				1: X + show
*			4:N_Y
*				0: X - no show
*				1: X - show
*			3:P_Z
*				0: X + no show
*				1: X + show
*			2:N_Z
*				0: X - no show
*				1: X - show
*			1:P_V
*				0: X + no show
*				1: X + show
*			0:N_V
*				0: X - no show
*				1: X - show
*/
#define LIS3DSH_OUTS2_ADDR					0x7f
#define _LIS3DSH_P_X		7
#define _LIS3DSH_N_X		6
#define _LIS3DSH_P_Y		5
#define _LIS3DSH_N_Y		4
#define _LIS3DSH_P_Z		3
#define _LIS3DSH_N_Z		2
#define _LIS3DSH_P_V		1
#define _LIS3DSH_N_V		0

/*	Rejestr PEAK2 ------------ Peak value ---------------------------------------------------------
*	Default value: ---
*	Read only register
*
*	Peak detection value register for SM2 operation.
*/
#define LIS3DSH_PEAK2_ADDR					0x1a

/*	Rejestr DES2 ------------- Decimation factor --------------------------------------------------
*	Default value: ---
*	Write only register
*
*	Decimation counter value register for SM2 operation.
*/
#define LIS3DSH_DES2_ADDR					0x78

/**************************************************************************************************
 * Registers marked as ‘Reserved’ must not be changed. The writing to those registers may		  *
 * cause permanent damages to the device. The content of the registers that are loaded 			  *
 * at boot should not be changed. They contain the factory calibration values. 					  *
 * Their content is automatically restored when the device is powered up.						  *
 **************************************************************************************************/

#define LIS3DSH_CS_LOW()       GPIO_ResetBits(LIS3DSH_SPI_CS_GPIO_PORT, LIS3DSH_SPI_CS_PIN)
#define LIS3DSH_CS_HIGH()      GPIO_SetBits(LIS3DSH_SPI_CS_GPIO_PORT, LIS3DSH_SPI_CS_PIN)

void lis3dsh_init();
void lis3dsh_set_OutputDataRate(lis3dsh_register odr_selection);
void lis3dsh_AxesEnable(lis3dsh_register axes);
void lis3dsh_int1_enable();
void lis3dsh_ReadAxes(LIS3DSH_OutXYZTypeDef* axes);
lis3dsh_register lis3dsh_read_register(lis3dsh_register addres);
void lis3dsh_read_block(uint8_t* buf, uint8_t addres, uint16_t size);
void lis3dsh_write_register(lis3dsh_register addres,lis3dsh_register value);
void lis3dsh_write_block(lis3dsh_register* buf,lis3dsh_register addres,lis3dsh_register size);

uint8_t lis3dsh_timeout_usercallback(void);

#endif /* STM32F4_DISCOVERY_LIS3DSH_H_ */
