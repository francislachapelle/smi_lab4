/*
 * spi.c
 *
 *  Created on: Nov 7, 2018
 *      Author: franc
 */
#include "stm32f4_discovery.h"
#include <spi.h>
#include <stdint.h>

uint8_t sendByteEEPROM(uint8_t byte);
uint8_t readByteEEPROM(uint8_t byte);
void    writeEnableEEPROM(void);
void	startReadSequenceEEPROM(uint16_t address);
void 	startWriteSequenceEEPROM(uint16_t address);
void 	waitWriteProcessEEPROM(void);

void initSPI(void)
{
	SPI_InitTypeDef   SPI_InitStruct;
	GPIO_InitTypeDef  GPIO_InitStructure;

	// Configure MOSI, MISO and SCK
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);
	GPIO_InitStructure.GPIO_Pin = SPI_MOSI | SPI_MISO | SPI_SCK;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// Configure CS, HOLD and WP
	GPIO_InitStructure.GPIO_Pin = SPI_CS | SPI_HOLD | SPI_WP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_SetBits(GPIOA, SPI_WP | SPI_HOLD);

	CS_HIGH();

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

    SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
    SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
    SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStruct.SPI_CRCPolynomial = 7;

    SPI_Init(SPI1, &SPI_InitStruct);

    SPI_Cmd(SPI1, ENABLE);


}

char LireMemoireEEPROM (unsigned int AdresseEEPROM,
					    unsigned int NbreOctets,
						unsigned char *Destination)
{


	startReadSequenceEEPROM(AdresseEEPROM);

	while (NbreOctets--)
	{
		*Destination =  sendByteEEPROM(0);
		++Destination;
	}

	CS_HIGH();

	return 0;
}


char EcrireMemoireEEPROM (unsigned int AdresseEEPROM,
					      unsigned int NbreOctets,
						  unsigned char *Source)
{
	writeEnableEEPROM();
	startWriteSequenceEEPROM(AdresseEEPROM);

	while (NbreOctets--)
	{
		sendByteEEPROM(*Source);
		++Source;
	}

	CS_HIGH();

	waitWriteProcessEEPROM();

	return 0;
}

/********************************************
 * Private function declarations
 */

void startWriteSequenceEEPROM(uint16_t address)
{
	CS_LOW();

	sendByteEEPROM(EEPROM_CMD_WRITE);
	sendByteEEPROM((address & 0xFF00) >> 8);
	sendByteEEPROM((address & 0xFF));

}

void startReadSequenceEEPROM(uint16_t address)
{
	CS_LOW();

	sendByteEEPROM(EEPROM_CMD_READ);
	sendByteEEPROM((address & 0xFF00) >> 8);
	sendByteEEPROM((address & 0xFF));
}

void waitWriteProcessEEPROM(void)
{
	SPI_STATUS_t eeprom_status = 0;

	CS_LOW();

	sendByteEEPROM(EEPROM_CMD_READ_STATUS);

	do
	{
		eeprom_status = sendByteEEPROM(0);
	}
	while (eeprom_status & SPI_STATUS_WRITE_IN_PROCESS);

	CS_HIGH();
}

void writeEnableEEPROM(void)
{
	CS_LOW();

	sendByteEEPROM(EEPROM_CMD_WRITE_ENABLE);

	CS_HIGH();
}

uint8_t sendByteEEPROM(uint8_t byte)
{
	// Stay there until DR register is empty
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);

	// Send byte through SPI1
	SPI_I2S_SendData(SPI1, byte);

	// Wait until byte is received
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);

	return SPI_I2S_ReceiveData(SPI1);
}

uint8_t readByteEEPROM(uint8_t byte)
{
	return sendByteEEPROM(0);
}
