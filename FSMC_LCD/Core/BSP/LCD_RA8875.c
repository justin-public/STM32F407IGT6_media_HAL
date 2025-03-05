/*
 * LCD_RA8875.c
 *
 *  Created on: Feb 27, 2025
 *      Author: compro
 */
#include "bsp.h"
#include "bsp_ra8875_port.h"

static __IO uint8_t s_ucRA8875Busy = 0;

static uint16_t s_WinX = 0;
static uint16_t s_WinY = 0;
static uint16_t s_WinHeight = 272;
static uint16_t s_WinWidth = 480;

static void RA8875_SetCursor(uint16_t _usX, uint16_t _usY);
static void RA8875_WriteReg(uint8_t _ucRegAddr, uint8_t _ucRegValue);
static void RA8875_SetTextCursor(uint16_t _usX, uint16_t _usY);
static void BTE_SetTarBlock(uint16_t _usX, uint16_t _usY, uint16_t _usHeight, uint16_t _usWidth, uint8_t _ucLayer);
static void BTE_SetOperateCode(uint8_t _ucOperate);
static void BTE_Start(void);
static void BTE_Wait(void);

void RA8875_ClrScr(uint16_t _usColor)
{
    BTE_SetTarBlock(s_WinX, s_WinY, s_WinHeight, s_WinWidth, 0);
    BTE_SetOperateCode(0x0C);
    RA8875_SetFrontColor(_usColor);	
    BTE_Start();
    BTE_Wait();
}

static void BTE_SetTarBlock(uint16_t _usX, uint16_t _usY, uint16_t _usHeight, uint16_t _usWidth, uint8_t _ucLayer)
{
    RA8875_WriteReg(0x58, _usX);
	RA8875_WriteReg(0x59, _usX >> 8);

    RA8875_WriteReg(0x5A, _usY);
    if(_ucLayer == 0)
    {
        RA8875_WriteReg(0x5B, _usY >> 8);
    }
    else
    {
        RA8875_WriteReg(0x5B, (1 << 7) | (_usY >> 8));
    }
    RA8875_WriteReg(0x5C, _usWidth);
	RA8875_WriteReg(0x5D, _usWidth >> 8);

	RA8875_WriteReg(0x5E, _usHeight);
	RA8875_WriteReg(0x5F, _usHeight >> 8);
}

static void RA8875_WriteReg(uint8_t _ucRegAddr, uint8_t _ucRegValue)
{
    s_ucRA8875Busy = 1;
    
    RA8875_WriteCmd(_ucRegAddr);
    RA8875_WriteData(_ucRegValue);
    
    s_ucRA8875Busy = 0;
}

void RA8875_SetFrontColor(uint16_t _usColor)
{
    RA8875_WriteReg(0x63, (_usColor & 0xF800) >> 11);	/* R5  */
	RA8875_WriteReg(0x64, (_usColor & 0x07E0) >> 5);	/* G6 */
	RA8875_WriteReg(0x65, (_usColor & 0x001F));			/* B5 */
}

void RA8875_DrawBMP(uint16_t _usX, uint16_t _usY, uint16_t _usHeight, uint16_t _usWidth, uint16_t *_ptr)
{
    uint32_t index = 0;
	const uint16_t *p;

    RA8875_SetDispWin(_usX, _usY, _usHeight, _usWidth);
}

void RA8875_SetDispWin(uint16_t _usX, uint16_t _usY, uint16_t _usHeight, uint16_t _usWidth)
{
    uint16_t usTemp;

    RA8875_WriteReg(0x30, _usX);
    RA8875_WriteReg(0x31, _usX >> 8);

    RA8875_WriteReg(0x32, _usY);
    RA8875_WriteReg(0x33, _usY >> 8);

    usTemp = _usWidth + _usX - 1;
    RA8875_WriteReg(0x34, usTemp);
    RA8875_WriteReg(0x35, usTemp >> 8);

    usTemp = _usHeight + _usY - 1;
    RA8875_WriteReg(0x36, usTemp);
    RA8875_WriteReg(0x37, usTemp >> 8);

    RA8875_SetCursor(_usX, _usY);
    
    s_WinX = _usX;
	s_WinY = _usY;
	s_WinHeight = _usHeight;
	s_WinWidth = _usWidth;
}

static void RA8875_SetCursor(uint16_t _usX, uint16_t _usY)
{
    RA8875_WriteReg(0x46, _usX);
    RA8875_WriteReg(0x47, _usX >> 8);
	RA8875_WriteReg(0x48, _usY);
	RA8875_WriteReg(0x49, _usY >> 8);
}

void RA8875_PutPixel(uint16_t _usX, uint16_t _usY, uint16_t _usColor)
{
    s_ucRA8875Busy = 1;
    
    RA8875_WriteCmd(0x46); RA8875_WriteData(_usX);
    RA8875_WriteCmd(0x47); RA8875_WriteData(_usX >> 8);
	RA8875_WriteCmd(0x48); RA8875_WriteData(_usY);
	RA8875_WriteCmd(0x49); RA8875_WriteData(_usY >> 8);

    RA8875_WriteCmd(0x02); 		
	RA8875_WriteData16(_usColor);
    
    s_ucRA8875Busy = 0;
}

void RA8875_SetBackLight(uint8_t _bright)
{
    if (_bright == 0)
    {
        RA8875_WriteReg(0x8A, 0 << 6);
    }
    else if(_bright == BRIGHT_MAX)
    {
        RA8875_WriteReg(0x8A, 1 << 6);
    }
    else
    {
        RA8875_WriteReg(0x8A, (1 << 7) | 12);
        RA8875_WriteReg(0x8B, _bright);
    }
}

void RA8875_SetBackColor(uint16_t _usColor)
{
    RA8875_WriteReg(0x60, (_usColor & 0xF800) >> 11);
    RA8875_WriteReg(0x61, (_usColor & 0x07E0) >> 5);	
	RA8875_WriteReg(0x62, (_usColor & 0x001F));			
}

void RA8875_SetFont(uint8_t _ucFontType, uint8_t _ucLineSpace, uint8_t _ucCharSpace)
{
    if (_ucLineSpace >31)
    {
        _ucLineSpace = 31;
    }
    RA8875_WriteReg(0x29, _ucLineSpace);
    if (_ucCharSpace > 63)
	{
		_ucCharSpace = 63;
	}
    if (_ucFontType > RA_FONT_32)
    {
        _ucFontType = RA_FONT_16;
    }
    RA8875_WriteReg(0x2E, (_ucCharSpace & 0x3F) | (_ucFontType << 6));
}

void RA8875_SetTextZoom(uint8_t _ucHSize, uint8_t _ucVSize)
{
    RA8875_WriteReg(0x22, ((_ucHSize & 0x03) << 2) | ( _ucVSize & 0x03));
}

void RA8875_DispStr(uint16_t _usX, uint16_t _usY, char *_ptr)
{
    /*
    RA8875 드라이버 설정 – Genitop Inc.RA8875는 폰트 ROM을 구동하는 데 사용됩니다. 
    시스템은 그래픽 폰트를 지원하며, 이를 DDRAM 인터페이스를 통해 표시합니다. 
    RA8875는 다양한 폰트를 지원하며, 예를 들어 GT21L16TW/GT21H16T1W, GT23L16U2W 등의 모델을 포함하고, 
    16x16, 24x24, 32x32 점 크기 등의 표준 폰트 크기를 지원합니다.
    */
    RA8875_SetTextCursor(_usX, _usY);
    RA8875_WriteReg(0x40, (1 << 7));
    RA8875_WriteReg(0x06, (3 << 0));
    RA8875_WriteReg(0x21, (0 << 7) | (1 << 5));
    RA8875_WriteReg(0x05, (0 << 7) | (0 << 6) | (1 << 5) | (1 << 3) | (0 << 2) | (0 << 1));
    RA8875_WriteReg(0x2F, (4 << 5) | (0 << 2) | (1 << 0));

    s_ucRA8875Busy = 1;
    RA8875_WriteCmd(0x02);

    while (*_ptr != 0)
    {
        RA8875_WriteData(*_ptr);
        while ((RA8875_ReadStatus() & 0x80) == 0x80); 
        _ptr++;    
    }
    s_ucRA8875Busy = 0;

    RA8875_WriteReg(0x40, (0 << 7));
}

static void RA8875_SetTextCursor(uint16_t _usX, uint16_t _usY)
{
    RA8875_WriteReg(0x2A, _usX);
	RA8875_WriteReg(0x2B, _usX >> 8);
	RA8875_WriteReg(0x2C, _usY);
	RA8875_WriteReg(0x2D, _usY >> 8);
}

void RA8875_WaitBusy(void)
{
    while ((RA8875_ReadStatus() & 0x80) == 0x80);
}

void RA8875_DrawCircle(uint16_t _usX, uint16_t _usY, uint16_t _usRadius, uint16_t _usColor)
{
    if (_usRadius > 255)
	{
		return;
	}
    RA8875_WriteReg(0x99, _usX);
	RA8875_WriteReg(0x9A, _usX >> 8);
	RA8875_WriteReg(0x9B, _usY);
	RA8875_WriteReg(0x9C, _usY >> 8);

	RA8875_WriteReg(0x9D, _usRadius);
    RA8875_SetFrontColor(_usColor);
    
    s_ucRA8875Busy = 1;
    RA8875_WriteCmd(0x90);
    RA8875_WriteData( (1 << 6) | (0 << 5));

    RA8875_WaitBusy();
    s_ucRA8875Busy = 0;
}

void RA8875_DrawRect(uint16_t _usX, uint16_t _usY, uint16_t _usHeight, uint16_t _usWidth, uint16_t _usColor)
{
    RA8875_WriteReg(0x91, _usX);
	RA8875_WriteReg(0x92, _usX >> 8);
	RA8875_WriteReg(0x93, _usY);
	RA8875_WriteReg(0x94, _usY >> 8);

    RA8875_WriteReg(0x95, _usX + _usWidth - 1);
	RA8875_WriteReg(0x96, (_usX + _usWidth - 1) >> 8);
	RA8875_WriteReg(0x97, _usY + _usHeight - 1);
	RA8875_WriteReg(0x98, (_usY + _usHeight - 1) >> 8);

    RA8875_SetFrontColor(_usColor);

    s_ucRA8875Busy = 1;
    RA8875_WriteCmd(0x90);
    RA8875_WriteData((1 << 7) | (0 << 5) | (1 << 4) | (0 << 0));
    RA8875_WaitBusy();
    s_ucRA8875Busy = 0;
}

void RA8875_FillRect(uint16_t _usX, uint16_t _usY, uint16_t _usHeight, uint16_t _usWidth, uint16_t _usColor)
{
    RA8875_WriteReg(0x91, _usX);
	RA8875_WriteReg(0x92, _usX >> 8);
	RA8875_WriteReg(0x93, _usY);
	RA8875_WriteReg(0x94, _usY >> 8);

    RA8875_WriteReg(0x95, _usX + _usWidth - 1);
	RA8875_WriteReg(0x96, (_usX + _usWidth - 1) >> 8);
	RA8875_WriteReg(0x97, _usY + _usHeight - 1);
	RA8875_WriteReg(0x98, (_usY + _usHeight - 1) >> 8);

    RA8875_SetFrontColor(_usColor);

    s_ucRA8875Busy = 1;

    RA8875_WriteCmd(0x90);
    RA8875_WriteData((1 << 7) | (1 << 5) | (1 << 4) | (0 << 0));

    RA8875_WaitBusy();

    s_ucRA8875Busy = 0;
}

static void BTE_SetOperateCode(uint8_t _ucOperate)
{
    RA8875_WriteReg(0x51, _ucOperate);
}

static void BTE_Start(void)
{
    s_ucRA8875Busy = 1;
	/* RA8875_WriteReg(0x50, 0x80);  ²»ÄÜÊ¹ÓÃÕâ¸öº¯Êý£¬ÒòÎªÄÚ²¿ÒÑ¾­²Ù×÷ÁË s_ucRA8875Busy ±êÖ¾ */
	RA8875_WriteCmd(0x50);	
	RA8875_WriteData(0x80);	
}

static void BTE_Wait(void)
{
    while ((RA8875_ReadStatus() & 0x40) == 0x40);
    s_ucRA8875Busy = 0;
}


