/*
 * spi.h
 *
 *  Created on: Nov 7, 2018
 *      Author: franc
 */

#ifndef SPI_H_
#define SPI_H_
#include "stm32f4_discovery.h"

#define			EEPROM_CMD_READ				                   0x03
#define			EEPROM_CMD_WRITE 				               0x02
#define			EEPROM_CMD_WRITE_ENABLE			               0x06
#define			EEPROM_CMD_READ_STATUS			               0x05




typedef enum
{
	  SPI_MOSI = GPIO_Pin_7
	, SPI_MISO = GPIO_Pin_6
	, SPI_SCK  = GPIO_Pin_5
	, SPI_HOLD = GPIO_Pin_4
	, SPI_CS   = GPIO_Pin_3
	, SPI_WP   = GPIO_Pin_2
}	SPI_PINS_t;

typedef enum
{
	  SPI_STATUS_WRITE_ENABLED = 0x02
	, SPI_STATUS_WRITE_IN_PROCESS = 0x01
} SPI_STATUS_t;


#define			CS_LOW()									GPIO_ResetBits(GPIOA, SPI_CS)
#define			CS_HIGH()									GPIO_SetBits(GPIOA, SPI_CS)

void initSPI (void);
char LireMemoireEEPROM (unsigned int AdresseEEPROM,
					    unsigned int NbreOctets,
						unsigned char *Destination);
char EcrireMemoireEEPROM (unsigned int AdresseEEPROM,
					      unsigned int NbreOctets,
						  unsigned char *Source);

#endif /* SPI_H_ */
