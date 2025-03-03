/*
 * bsp_tft_lcd.c
 *
 *  Created on: Feb 27, 2025
 *      Author: compro
 */
#include "bsp.h"
#include "fonts.h"

uint16_t g_LcdWidth = 400;

uint16_t LCD_GetWidth(void)
{
	return g_LcdWidth;
}

uint16_t LCD_GetHeight(void)
{
	return g_LcdHeight;
}

void LCD_ClrScr(uint16_t _usColor)
{
    if (g_ChipID == IC_8875)
    {
        RA8875_ClrScr(_usColor);
    }
    else
    {
        SPFD5420_ClrScr(_usColor);
    }
}

void LCD_DrawBMP(uint16_t _usX, uint16_t _usY, uint16_t _usHeight, uint16_t _usWidth, uint16_t *_ptr)
{
    if (g_ChipID == IC_8875)
    {
        RA8875_DrawBMP(_usX, _usY, _usHeight, _usWidth, _ptr);
    }
    else
    {

    }
}

uint16_t Blend565(uint16_t src, uint16_t dst, uint8_t alpha)
{
    uint32_t src2;
	uint32_t dst2;

    src2 = ((src << 16) |src) & 0x07E0F81F;
    dst2 = ((dst << 16) | dst) & 0x07E0F81F;
    dst2 = ((((dst2 - src2) * alpha) >> 5) + src2) & 0x07E0F81F;
    return (dst2 >> 16) | dst2;
}

void LCD_DrawIcon32(const ICON_T *_tIcon, FONT_T *_tFont, uint8_t _ucFocusMode)
{
    const uint8_t *p;
	uint16_t usOldRGB, usNewRGB;
	int16_t x, y;		
	uint8_t R1,G1,B1,A;	
	uint8_t R0,G0,B0;	

    p = (const uint8_t *)_tIcon->pBmp;
    p += 54;

    for (y = _tIcon->Height - 1; y >= 0; y--)
    {
        for (x = 0; x < _tIcon->Width; x++)
        {
            B1 = *p++;
			G1 = *p++;
			R1 = *p++;
			A = *p++;

            if (A == 0x00)	
			{
				;	
			}
            else if (A == 0xFF)
            {
                usNewRGB = RGB(R1, G1, B1);
                if (_ucFocusMode == 1)
				{
					usNewRGB = Blend565(usNewRGB, CL_YELLOW, 10);
				}
                LCD_PutPixel(x + _tIcon->Left, y + _tIcon->Top, usNewRGB);
            }
            else
            {
                usOldRGB = LCD_GetPixel(x + _tIcon->Left, y + _tIcon->Top);
                R0 = RGB565_R(usOldRGB);
				G0 = RGB565_G(usOldRGB);
				B0 = RGB565_B(usOldRGB);

                R1 = (R1 * A) / 255 + R0 * (255 - A) / 255;
				G1 = (G1 * A) / 255 + G0 * (255 - A) / 255;
				B1 = (B1 * A) / 255 + B0 * (255 - A) / 255;
				usNewRGB = RGB(R1, G1, B1);
                if (_ucFocusMode == 1)
				{
					usNewRGB = Blend565(usNewRGB, CL_YELLOW, 10);
				}
                LCD_PutPixel(x + _tIcon->Left, y + _tIcon->Top, usNewRGB);    
            }
        }
    }
    {
        uint16_t len;
		uint16_t width;
        
        len = strlen(_tIcon->Text);

        if  (len == 0)
		{
			return;	
		}
        if (_tFont->FontCode == FC_ST_12)
        {
            width = 6 * (len + _tFont->Space);
        }
        else
        {
            width = 8 * (len + _tFont->Space);
        }
        x = (_tIcon->Left + _tIcon->Width / 2) - width / 2;
		y = _tIcon->Top + _tIcon->Height + 2;
		LCD_DispStr(x, y, (char *)_tIcon->Text, _tFont);
    }
}