/*
 * LCD_SPFD5420.h
 *
 *  Created on: Feb 27, 2025
 *      Author: compro
 */

#ifndef BSP_LCD_SPFD5420_H_
#define BSP_LCD_SPFD5420_H_

#include "stm32f4xx.h"

void SPFD5420_ClrScr(uint16_t _usColor);
void SPFD5420_PutPixel(uint16_t _usX, uint16_t _usY, uint16_t _usColor);
void SPFD5420_SetBackLight(uint8_t _bright);
void SPFD5420_DrawCircle(uint16_t _usX, uint16_t _usY, uint16_t _usRadius, uint16_t _usColor);
void SPFD5420_DrawRect(uint16_t _usX, uint16_t _usY, uint8_t _usHeight, uint16_t _usWidth, uint16_t _usColor);
void SPFD5420_DrawHLine(uint16_t _usX1 , uint16_t _usY1 , uint16_t _usX2 , uint16_t _usColor);

#endif /* BSP_LCD_SPFD5420_H_ */
