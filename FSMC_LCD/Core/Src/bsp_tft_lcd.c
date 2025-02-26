/*
 * bsp_tft_lcd.c
 *
 *  Created on: Feb 26, 2025
 *      Author: compro
 */
#include "bsp.h"
#include "fonts.h"

uint16_t g_ChipID = IC_4001;
uint16_t g_LcdWidth = 400;			

void LCD_ClrScr(uint16_t _usColor)
{
    if (g_ChipID == IC_8875)
    {
        RA8875_ClrScr(_usColor);
    }
}