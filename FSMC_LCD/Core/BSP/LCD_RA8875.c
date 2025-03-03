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
