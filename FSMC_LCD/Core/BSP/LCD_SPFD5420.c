/*
 * LCD_SPFD5420.c
 *
 *  Created on: Feb 27, 2025
 *      Author: compro
 */
#include "stm32f4xx.h"
#include <stdio.h>
#include <string.h>
#include "bsp_tft_lcd.h"
#include "fonts.h"

#define SPFD5420_BASE       ((uint32_t)(0x60000000 | 0x00000000))
#define SPFD5420_REG		*(__IO uint16_t *)(SPFD5420_BASE)
#define SPFD5420_RAM		*(__IO uint16_t *)(SPFD5420_BASE + (1 << 19))

static void SPFD5420_SetCursor(uint16_t _usX, uint16_t _usY);
static void SPFD5420_WriteReg(__IO uint16_t _usAddr, uint16_t _usValue);

// 2025.02.27 this..
void SPFD5420_ClrScr(uint16_t _usColor)
{
    uint32_t i;
    SPFD5420_SetCursor(0, 0);
    SPFD5420_REG = 0x202;

    for (i = 0; i < g_LcdHeight * g_LcdWidth; i++)
    {
        SPFD5420_RAM = _usColor;
    }
}

static void SPFD5420_SetCursor(uint16_t _usX, uint16_t _usY)
{
    SPFD5420_WriteReg(0x0200, _usY);
    SPFD5420_WriteReg(0x0201, 399 - _usX);
}

static void SPFD5420_WriteReg(__IO uint16_t _usAddr, uint16_t _usValue)
{
    SPFD5420_REG = _usAddr;
    SPFD5420_RAM = _usValue;
}
