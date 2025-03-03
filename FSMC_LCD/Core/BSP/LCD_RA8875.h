/*
 * LCD_RA8875.h
 *
 *  Created on: Feb 27, 2025
 *      Author: compro
 */

#ifndef BSP_LCD_RA8875_H_
#define BSP_LCD_RA8875_H_

void RA8875_ClrScr(uint16_t _usColor);
void RA8875_SetFrontColor(uint16_t _usColor);
void RA8875_DrawBMP(uint16_t _usX, uint16_t _usY, uint16_t _usHeight, uint16_t _usWidth, uint16_t *_ptr);
void RA8875_SetDispWin(uint16_t _usX, uint16_t _usY, uint16_t _usHeight, uint16_t _usWidth);

#endif /* BSP_LCD_RA8875_H_ */
