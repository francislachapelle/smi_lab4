/*
******************************************************************************
File:     main.c
Info:     Generated by Atollic TrueSTUDIO(R) 9.0.0   2018-11-07

The MIT License (MIT)
Copyright (c) 2018 STMicroelectronics

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

******************************************************************************
*/

/* Includes */

#include "stm32f4_discovery.h"
#include "spi.h"

/* Private macro */
/* Private variables */
/* Private function prototypes */
/* Private functions */
	GPIO_InitTypeDef  GPIO_InitStructure;
/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/
int main(void)
{

  /* TODO - Add your application code here */
	unsigned char valeur_lue[4] = {0, 0, 0, 0};
	unsigned char valeur_a_ecrire_1 = 0x0F;
	unsigned int adresse_1 = 0x00;
	unsigned char valeur_a_ecrire_2[2] = {0xFF, 0x0F};
	unsigned int adresse_2 = 0x01;
	unsigned char valeur_a_ecrire_3[3] = {0xFF, 0x14, 0x14};
	unsigned int adresse_3 = 0x02;

	initSPI();
	EcrireMemoireEEPROM(adresse_1, 1, &valeur_a_ecrire_1);
	LireMemoireEEPROM(adresse_1, 1, &valeur_lue[0]);
	EcrireMemoireEEPROM(adresse_2, 2, &valeur_a_ecrire_2[0]);
	LireMemoireEEPROM(adresse_2, 2, &valeur_lue[0]);
	EcrireMemoireEEPROM(adresse_3, 3, &valeur_a_ecrire_3[0]);
	LireMemoireEEPROM(adresse_3, 3, &valeur_lue[0]);

  /* Infinite loop */
	while (1)
	{

	}
}
