/*
 * bsp_tft_lcd.c
 *
 *  Created on: Feb 27, 2025
 *      Author: compro
 */
#include "bsp.h"
#include "fonts.h"

uint16_t g_LcdWidth = 400;
uint8_t s_ucBright;

static void LCD_CtrlLinesConfig(void);
static void LCD_FSMCConfig(void);

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

static void LCD_CtrlLinesConfig(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_FSMC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 |
                       GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 |
                       GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_FSMC;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 |
                       GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 |
                       GPIO_PIN_15;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_12;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
}

static void LCD_FSMCConfig(void)
{
    FSMC_NORSRAM_InitTypeDef init;
    FSMC_NORSRAM_TimingTypeDef timingWrite;
    FSMC_NORSRAM_TimingTypeDef timingRead;

    /* FSMC 타이밍 설정 - 읽기 */
    timingRead.AddressSetupTime = 2;
    timingRead.AddressHoldTime = 0;
    timingRead.DataSetupTime = 5;
    timingRead.BusTurnAroundDuration = 0;
    timingRead.CLKDivision = 0;
    timingRead.DataLatency = 0;
    timingRead.AccessMode = FSMC_ACCESS_MODE_A;

    /* FSMC 타이밍 설정 - 쓰기 */
    timingWrite.AddressSetupTime = 2;
    timingWrite.AddressHoldTime = 0;
    timingWrite.DataSetupTime = 5;
    timingWrite.BusTurnAroundDuration = 0;
    timingWrite.CLKDivision = 0;
    timingWrite.DataLatency = 0;
    timingWrite.AccessMode = FSMC_ACCESS_MODE_A;

    /* FSMC NORSRAM 컨트롤러 초기화 */
    init.NSBank = FSMC_NORSRAM_BANK4;           /* LCD는 BANK4에 연결 */
    init.DataAddressMux = FSMC_DATA_ADDRESS_MUX_DISABLE;
    init.MemoryType = FSMC_MEMORY_TYPE_SRAM;
    init.MemoryDataWidth = FSMC_NORSRAM_MEM_BUS_WIDTH_16;
    init.BurstAccessMode = FSMC_BURST_ACCESS_MODE_DISABLE;
    init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW;
    init.WrapMode = FSMC_WRAP_MODE_DISABLE;
    init.WaitSignalActive = FSMC_WAIT_TIMING_BEFORE_WS;
    init.WriteOperation = FSMC_WRITE_OPERATION_ENABLE;
    init.WaitSignal = FSMC_WAIT_SIGNAL_DISABLE;
    init.ExtendedMode = FSMC_EXTENDED_MODE_DISABLE;      /* Extended Mode 비활성화 */
    init.AsynchronousWait = FSMC_ASYNCHRONOUS_WAIT_DISABLE;
    init.WriteBurst = FSMC_WRITE_BURST_DISABLE;
    init.ContinuousClock = FSMC_CONTINUOUS_CLOCK_SYNC_ONLY;
    init.WriteFifo = FSMC_WRITE_BURST_ENABLE;
    init.PageSize = FSMC_PAGE_SIZE_NONE;

    FSMC_NORSRAM_Init(FSMC_NORSRAM_DEVICE, &init);
    FSMC_NORSRAM_Timing_Init(FSMC_NORSRAM_DEVICE, &timingRead, FSMC_NORSRAM_BANK4);
    if (init.ExtendedMode == FSMC_EXTENDED_MODE_ENABLE) {
        FSMC_NORSRAM_Extended_Timing_Init(FSMC_NORSRAM_EXTENDED_DEVICE, &timingWrite, FSMC_NORSRAM_BANK4, FSMC_EXTENDED_MODE_ENABLE);
    }
    /* FSMC BANK4 활성화 */
    FSMC_NORSRAM_EnableBank(FSMC_NORSRAM_BANK4);
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

void LCD_InitHard(void)
{
    uint16_t id;

    // LCD GPIO 설정
    LCD_CtrlLinesConfig();
    
    LCD_FSMCConfig();

    bsp_DelayMS(20);

    id = SPFD5420_ReadID();  	
    if ((id == 0x5420) || (id ==  0xB509) || (id == 0x5520))
    {
        SPFD5420_InitHard();
    }
    else
    {
        // 2025.03.08
        if (RA8875_ReadID() == 0x75)
        {

        }
    }
}

void LCD_DispStr(uint16_t _usX, uint16_t _usY, char *_ptr, FONT_T *_tFont)
{
    uint32_t i;
	uint8_t code1;
	uint8_t code2;
	uint32_t address;
	uint8_t buf[24 * 24 / 8];	
	uint8_t width;
	uint16_t m;
	uint8_t font_width,font_height, font_bytes;
	uint16_t x, y;
	const uint8_t *pAscDot;
#ifdef USE_SMALL_FONT
	const uint8_t *pHzDot;
#else
	uint32_t AddrHZK;
#endif
    if (_tFont->FontCode == FC_ST_12)
    {
        font_height = 12;
		font_width = 12;
		font_bytes = 24;
        pAscDot = g_Ascii12;
    
    #ifdef USE_SMALL_FONT
		pHzDot = g_Hz12;
	#else
		AddrHZK = HZK12_ADDR;
	#endif
    }
    else
    {
        font_height = 16;
		font_width = 16;
		font_bytes = 32;
		pAscDot = g_Ascii16;
    
    #ifdef USE_SMALL_FONT
		pHzDot = g_Hz16;
	#else
		AddrHZK = HZK16_ADDR;
	#endif
    }

    while (*_ptr != 0)
    {
        code1 = *_ptr;
        if (code1 < 0x80)
        {
            memcpy(buf, &pAscDot[code1 * (font_bytes / 2)], (font_bytes / 2));
            width = font_width / 2;
        }
        else
        {
            code2 = *++_ptr;
            if(code2 == 0)
            {
                break;
            }
            #ifdef USE_SMALL_FONT
                m = 0;
                while (1)
                {
                    address = m * (font_bytes + 2);
                    m++;
                    if ((code1 == pHzDot[address + 0]) && (code2 == pHzDot[address + 1]))
                    {
                        address += 2;
                        memcpy(buf, &pHzDot[address], font_bytes);
                        break;
                    }
                    else if((pHzDot[address + 0] == 0xFF) && (pHzDot[address + 1] == 0xFF))
                    {
                        memset(buf, 0xFF, font_bytes);
                        break;
                    }
                }
            #else
                if (code1 >=0xA1 && code1 <= 0xA9 && code2 >=0xA1)
                {
                    address = ((code1 - 0xA1) * 94 + (code2 - 0xA1)) * font_bytes + AddrHZK;
                }      
                else if (code1 >=0xB0 && code1 <= 0xF7 && code2 >=0xA1)
                {
                    address = ((code1 - 0xB0) * 94 + (code2 - 0xA1) + 846) * font_bytes + AddrHZK;
                }
                memcpy(buf, (const uint8_t *)address, font_bytes);
            #endif
                width = font_width; 
        }
        y = _usY;
        for (m = 0; m < font_height; m++)
        {
            x = _usX;
            for (i = 0; i < width; i++)
            {
                if ((buf[m * ((2 * width) / font_width) + i / 8] & (0x80 >> (i % 8 ))) != 0x00)
                {
                    LCD_PutPixel(x, y, _tFont->FrontColor);
                }
                else
                {
                    if (_tFont->BackColor != CL_MASK)
                    {
                        LCD_PutPixel(x, y, _tFont->BackColor);
                    }
                }
                x++;
            }
            y++;
        }
        if (_tFont->Space > 0)
        {

        }
        _usX += width + _tFont->Space;
        _ptr++;
    }
}

void LCD_PutPixel(uint16_t _usX, uint16_t _usY, uint16_t _usColor)
{
    if (g_ChipID == IC_8875)
    {
        RA8875_PutPixel(_usX, _usY, _usColor);
    }
    else
    {
        SPFD5420_PutPixel(_usX, _usY, _usColor);
    }
}

void LCD_SetBackLight(uint8_t _bright)
{
    s_ucBright =  _bright;

    if (g_ChipID == IC_8875)
    {
        RA8875_SetBackLight(_bright);
    }
    else
    {
        SPFD5420_SetBackLight(_bright);
    }
}

void LCD_GetChipDescribe(char *_str)
{
    switch (g_ChipID)
    {
        case IC_5420:
			strcpy(_str, CHIP_STR_5420);
			break;
        
        case IC_4001:
			strcpy(_str, CHIP_STR_4001);
			break;
        
        case IC_61509:
			strcpy(_str, CHIP_STR_61509);
			break;
        
        case IC_8875:
			strcpy(_str, CHIP_STR_8875);
			break;
        
        default:
			strcpy(_str, "Unknow");
			break;
    }
}

void LCD_DrawCircle(uint16_t _usX, uint16_t _usY, uint16_t _usRadius, uint16_t _usColor)
{
    if (g_ChipID == IC_8875)
    {
        RA8875_DrawCircle(_usX, _usY, _usRadius, _usColor);
    }
    else
    {
        SPFD5420_DrawCircle(_usX, _usY, _usRadius, _usColor);
    }
}

void LCD_DrawButton(BUTTON_T *_pBtn)
{
#if 1
    uint16_t len, fwidth, x, y;
    if (_pBtn->Focus == 1)
    {
        LCD_DrawRect(_pBtn->Left, _pBtn->Top, _pBtn->Height, _pBtn->Width, BUTTON_BORDER_COLOR);
        LCD_DrawRect(_pBtn->Left + 1, _pBtn->Top + 1, _pBtn->Height - 2, _pBtn->Width - 2, BUTTON_BORDER1_COLOR);
        LCD_DrawRect(_pBtn->Left + 2, _pBtn->Top + 2, _pBtn->Height - 4, _pBtn->Width - 4, BUTTON_BORDER2_COLOR);

        LCD_Fill_Rect(_pBtn->Left + 3, _pBtn->Top + 3, _pBtn->Height - 6, _pBtn->Width - 6, BUTTON_ACTIVE_COLOR);
    }
    else
    {
        LCD_DrawRect(_pBtn->Left, _pBtn->Top, _pBtn->Height, _pBtn->Width, BUTTON_BORDER_COLOR);
        LCD_DrawRect(_pBtn->Left + 1, _pBtn->Top + 1, _pBtn->Height - 2, _pBtn->Width - 2, BUTTON_BORDER1_COLOR);
		LCD_DrawRect(_pBtn->Left + 2, _pBtn->Top + 2, _pBtn->Height - 4, _pBtn->Width - 4, BUTTON_BORDER2_COLOR);

        LCD_Fill_Rect(_pBtn->Left + 3, _pBtn->Top + 3, _pBtn->Height - 6, _pBtn->Width - 6, BUTTON_BACK_COLOR);
    }
    len = strlen(_pBtn->pCaption);

    if(_pBtn->Font->FontCode == FC_ST_16)
    {
        fwidth = 8;
    }
    else if (_pBtn->Font->FontCode == FC_ST_12)
	{
		fwidth = 6;		
	}
    else
    {
        fwidth = 8;
    }
    x = _pBtn->Left + _pBtn->Width / 2 - (len * fwidth) / 2;
    y = _pBtn->Top + _pBtn->Height / 2 - fwidth;

    LCD_DispStr(x, y, _pBtn->pCaption, _pBtn->Font);
#else
    if (g_ChipID == IC_8875)
    {
        uint16_t len, x, y;
        if (_pBtn->Focus == 1)
		{
			RA8875_DrawRect(_pBtn->Left, _pBtn->Top, _pBtn->Height, _pBtn->Width, BUTTON_BORDER_COLOR);
			RA8875_DrawRect(_pBtn->Left + 1, _pBtn->Top + 1, _pBtn->Height - 2, _pBtn->Width - 2, BUTTON_BORDER1_COLOR);
			RA8875_DrawRect(_pBtn->Left + 2, _pBtn->Top + 2, _pBtn->Height - 4, _pBtn->Width - 4, BUTTON_BORDER2_COLOR);

			RA8875_FillRect(_pBtn->Left + 3, _pBtn->Top + 3, _pBtn->Height - 6, _pBtn->Width - 6, BUTTON_ACTIVE_COLOR);

			RA8875_SetBackColor(BUTTON_ACTIVE_COLOR);
		}
        else
        {
            RA8875_DrawRect(_pBtn->Left, _pBtn->Top, _pBtn->Height, _pBtn->Width, BUTTON_BORDER_COLOR);
			RA8875_DrawRect(_pBtn->Left + 1, _pBtn->Top + 1, _pBtn->Height - 2, _pBtn->Width - 2, BUTTON_BORDER1_COLOR);
			RA8875_DrawRect(_pBtn->Left + 2, _pBtn->Top + 2, _pBtn->Height - 4, _pBtn->Width - 4, BUTTON_BORDER2_COLOR);

			RA8875_FillRect(_pBtn->Left + 3, _pBtn->Top + 3, _pBtn->Height - 6, _pBtn->Width - 6, BUTTON_BACK_COLOR);

			RA8875_SetBackColor(BUTTON_BACK_COLOR);
        }
        #if 1
            if (strcmp(_pBtn->Caption, "¡û") == 0)
            {
                RA8875_SetFont(RA_FONT_16, 0, 0);
				RA8875_SetFrontColor(CL_BLACK);
				RA8875_SetTextZoom(RA_SIZE_X2, RA_SIZE_X2);
            }
            else
            {
                RA8875_SetFont(RA_FONT_16, 0, 0);
				RA8875_SetFrontColor(CL_BLACK);
				RA8875_SetTextZoom(RA_SIZE_X1, RA_SIZE_X1);
            }
        #else
            RA8875_SetFont(_pBtn->Font.FontCode, 0, 0);
			RA8875_SetFrontColor(_pBtn->Font.FrontColor);	
        #endif
        len = strlen(_pBtn->Caption);
        if (len != 3)
		{
		    x = _pBtn->Left + (_pBtn->Width - len * 16) / 2;
		}
		else
		{
			x = _pBtn->Left + (_pBtn->Width - len * 20) / 2;
		}
        if ((len == 1) && (_pBtn->Caption[0] == '.'))
        {
            y = _pBtn->Top + 3;
			x += 3;
        }
        else
        {
            y = _pBtn->Top + 3;
        }
        RA8875_DispStr(x, y, _pBtn->Caption);
        RA8875_SetTextZoom(RA_SIZE_X1, RA_SIZE_X1);	
    }
#endif
}

void LCD_DrawRect(uint16_t _usX, uint16_t _usY, uint16_t _usHeight, uint16_t _usWidth, uint16_t _usColor)
{
    if (g_ChipID == IC_8875)
    {
        RA8875_DrawRect(_usX, _usY, _usHeight, _usWidth, _usColor);
    }
    else
    {
        SPFD5420_DrawRect(_usX, _usY, _usHeight, _usWidth, _usColor);
    }
}

void LCD_Fill_Rect(uint16_t _usX, uint16_t _usY, uint16_t _usHeight, uint16_t _usWidth, uint16_t _usColor)
{
    uint16_t i;

    if (g_ChipID == IC_8875)
    {
        RA8875_FillRect(_usX, _usY, _usHeight, _usWidth, _usColor);
    }
    else
    {
        for (i = 0; i < _usHeight; i++)
        {
            SPFD5420_DrawHLine(_usX, _usY, _usX + _usWidth - 1, _usColor);
        }
    }
}
