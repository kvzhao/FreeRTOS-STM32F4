/*
 * stm32f4_discovery_lis3dsh.c
 *
 *  Created on: Dec 26, 2013
 *      Author: Pawel
 *
 *      IsNo 2013
 */

#include "stm32f4_discovery_lis3dsh.h"

__IO uint32_t  LIS3DSHTimeout = LIS3DSH_FLAG_TIMEOUT;

/* Read/Write command */
#define READWRITE_CMD              ((uint8_t)0x80)
/* Multiple byte read/write command */
#define MULTIPLEBYTE_CMD           ((uint8_t)0x40)
/* Dummy Byte Send by the SPI Master device in order to generate the Clock to the Slave device */
#define DUMMY_BYTE                 ((uint8_t)0x00)

static uint8_t _lis3dsh_sendbyte(uint8_t byte);

void lis3dsh_set_OutputDataRate(lis3dsh_register odr_selection)
{
	lis3dsh_register tmp;
	tmp=lis3dsh_read_register(LIS3DSH_CTRL_REG4_ADDR);
	tmp&=0x0f;
	tmp|=odr_selection;
	lis3dsh_write_register(LIS3DSH_CTRL_REG4_ADDR,tmp);
}
void lis3dsh_AxesEnable(lis3dsh_register axes)
{
	lis3dsh_register tmp;
	tmp=lis3dsh_read_register(LIS3DSH_CTRL_REG4_ADDR);
	tmp&=0xf8;
	tmp|=axes;
	lis3dsh_write_register(LIS3DSH_CTRL_REG4_ADDR,tmp);
}
void lis3dsh_int1_enable()
{
	lis3dsh_register tmp;
	tmp=lis3dsh_read_register(LIS3DSH_CTRL_REG3_ADDR);
	tmp|=(1<<_LIS3DSH_DR_EN)|
		 (1<<_LIS3DSH_IEA)  |
		 (1<<_LIS3DSH_INT1_EN);
	lis3dsh_write_register(LIS3DSH_CTRL_REG3_ADDR,tmp);
}
void lis3dsh_ReadAxes(LIS3DSH_OutXYZTypeDef* axes)
{
	uint8_t tmp=0;
	while(tmp==0)
		{
			tmp=lis3dsh_read_register(LIS3DSH_STATUS_ADDR);
			tmp&=(1<<_LIS3DSH_ZYXDA);
		}

	lis3dsh_read_block((lis3dsh_register*)axes,LIS3DSH_OUT_X_L_ADDR,6);
}
lis3dsh_register lis3dsh_read_register(lis3dsh_register addres)
{
	lis3dsh_register buffer;

	addres|=(uint8_t)READWRITE_CMD;
	LIS3DSH_CS_LOW();
	_lis3dsh_sendbyte(addres);
	buffer=_lis3dsh_sendbyte(DUMMY_BYTE);
	LIS3DSH_CS_HIGH();

	return buffer;
}
void lis3dsh_write_register(lis3dsh_register addres,lis3dsh_register value)
{
	LIS3DSH_CS_LOW();
	_lis3dsh_sendbyte(addres);
	_lis3dsh_sendbyte(value);
	LIS3DSH_CS_HIGH();
}
void lis3dsh_write_block(lis3dsh_register* buf,lis3dsh_register addres,lis3dsh_register size)
{
	while(size > 0x00)
	{
		lis3dsh_write_register(addres,*buf);
		size--;
		buf++;
		addres++;
	}
}

void lis3dsh_read_block(uint8_t* buf, uint8_t addres, uint16_t size)
{
	while(size > 0x00)
	  {
	    *buf = lis3dsh_read_register(addres);
	    size--;
	    buf++;
	    addres++;
	  }
}

void lis3dsh_init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;

// Enable the SPI
	RCC_APB2PeriphClockCmd(LIS3DSH_SPI_CLK, ENABLE);
	RCC_AHB1PeriphClockCmd(LIS3DSH_SPI_SCK_GPIO_CLK | LIS3DSH_SPI_MISO_GPIO_CLK | LIS3DSH_SPI_MOSI_GPIO_CLK, ENABLE);
	RCC_AHB1PeriphClockCmd(LIS3DSH_SPI_CS_GPIO_CLK, ENABLE);
// Enable INT1 GPIO clock
	RCC_AHB1PeriphClockCmd(LIS3DSH_SPI_INT1_GPIO_CLK, ENABLE);
// Enable INT2 GPIO clock
	RCC_AHB1PeriphClockCmd(LIS3DSH_SPI_INT2_GPIO_CLK, ENABLE);
	GPIO_PinAFConfig(LIS3DSH_SPI_SCK_GPIO_PORT, LIS3DSH_SPI_SCK_SOURCE, LIS3DSH_SPI_SCK_AF);
	GPIO_PinAFConfig(LIS3DSH_SPI_MISO_GPIO_PORT, LIS3DSH_SPI_MISO_SOURCE, LIS3DSH_SPI_MISO_AF);
	GPIO_PinAFConfig(LIS3DSH_SPI_MOSI_GPIO_PORT, LIS3DSH_SPI_MOSI_SOURCE, LIS3DSH_SPI_MOSI_AF);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

// SPI SCK pin configuration
	GPIO_InitStructure.GPIO_Pin = LIS3DSH_SPI_SCK_PIN;
	GPIO_Init(LIS3DSH_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);
// SPI  MOSI pin configuration
	GPIO_InitStructure.GPIO_Pin =  LIS3DSH_SPI_MOSI_PIN;
	GPIO_Init(LIS3DSH_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);
// SPI MISO pin configuration
	GPIO_InitStructure.GPIO_Pin = LIS3DSH_SPI_MISO_PIN;
	GPIO_Init(LIS3DSH_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

// SPI configuration ----------------------------------------------------------------------------
	SPI_I2S_DeInit(LIS3DSH_SPI);
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_Init(LIS3DSH_SPI, &SPI_InitStructure);
	// Enable SPI1
	SPI_Cmd(LIS3DSH_SPI, ENABLE);
	// Configure GPIO PIN for Lis Chip select */
	GPIO_InitStructure.GPIO_Pin = LIS3DSH_SPI_CS_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LIS3DSH_SPI_CS_GPIO_PORT, &GPIO_InitStructure);
//Deselect : Chip Select high */
	GPIO_SetBits(LIS3DSH_SPI_CS_GPIO_PORT, LIS3DSH_SPI_CS_PIN);
// Configure GPIO PINs to detect Interrupts */
	GPIO_InitStructure.GPIO_Pin = LIS3DSH_SPI_INT1_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(LIS3DSH_SPI_INT1_GPIO_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = LIS3DSH_SPI_INT2_PIN;
	GPIO_Init(LIS3DSH_SPI_INT2_GPIO_PORT, &GPIO_InitStructure);
}

static uint8_t _lis3dsh_sendbyte(uint8_t byte)
{
  /* Loop while DR register in not emplty */
	LIS3DSHTimeout = LIS3DSH_FLAG_TIMEOUT;
  while (SPI_I2S_GetFlagStatus(LIS3DSH_SPI, SPI_I2S_FLAG_TXE) == RESET)
  {
    if((LIS3DSHTimeout--) == 0) return lis3dsh_timeout_usercallback();
  }

  /* Send a Byte through the SPI peripheral */
  SPI_I2S_SendData(LIS3DSH_SPI, byte);

  /* Wait to receive a Byte */
  LIS3DSHTimeout = LIS3DSH_FLAG_TIMEOUT;
  while (SPI_I2S_GetFlagStatus(LIS3DSH_SPI, SPI_I2S_FLAG_RXNE) == RESET)
  {
    if((LIS3DSHTimeout--) == 0) return lis3dsh_timeout_usercallback();
  }

  /* Return the Byte read from the SPI bus */
  return (uint8_t)SPI_I2S_ReceiveData(LIS3DSH_SPI);
}

uint8_t lis3dsh_timeout_usercallback(void)
{
/* Block communication and all processes */
  while (1)
  {
  }
}
