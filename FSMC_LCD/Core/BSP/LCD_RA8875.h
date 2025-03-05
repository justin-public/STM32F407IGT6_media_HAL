/*
 * LCD_RA8875.h
 *
 *  Created on: Feb 27, 2025
 *      Author: compro
 */

#ifndef BSP_LCD_RA8875_H_
#define BSP_LCD_RA8875_H_

enum
{
	RA_FONT_16 = 0,		
	RA_FONT_24 = 1,		
	RA_FONT_32 = 2		
};

enum
{
	RA_SIZE_X1 = 0,		
	RA_SIZE_X2 = 1,		
	RA_SIZE_X3 = 2,		
	RA_SIZE_X4 = 3		
};

void RA8875_ClrScr(uint16_t _usColor);
void RA8875_SetFrontColor(uint16_t _usColor);
void RA8875_DrawBMP(uint16_t _usX, uint16_t _usY, uint16_t _usHeight, uint16_t _usWidth, uint16_t *_ptr);
void RA8875_SetDispWin(uint16_t _usX, uint16_t _usY, uint16_t _usHeight, uint16_t _usWidth);
void RA8875_PutPixel(uint16_t _usX, uint16_t _usY, uint16_t _usColor);
void RA8875_SetBackLight(uint8_t _bright);
void RA8875_SetBackColor(uint16_t _usColor);
void RA8875_SetFont(uint8_t _ucFontType, uint8_t _ucLineSpace, uint8_t _ucCharSpace);
void RA8875_SetTextZoom(uint8_t _ucHSize, uint8_t _ucVSize);
void RA8875_DispStr(uint16_t _usX, uint16_t _usY, char *_ptr);
void RA8875_DrawCircle(uint16_t _usX, uint16_t _usY, uint16_t _usRadius, uint16_t _usColor);
void RA8875_DrawRect(uint16_t _usX, uint16_t _usY, uint16_t _usHeight, uint16_t _usWidth, uint16_t _usColor);
void RA8875_FillRect(uint16_t _usX, uint16_t _usY, uint16_t _usHeight, uint16_t _usWidth, uint16_t _usColor);

#endif /* BSP_LCD_RA8875_H_ */
