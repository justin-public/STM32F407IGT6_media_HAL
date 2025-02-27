/*
 * main_menu.c
 *
 *  Created on: Feb 27, 2025
 *      Author: compro
 */
#include "bsp.h"
#include "images.h"
#include "main_enum.h"
#include "main_menu.h"

#define STYLE_COUNT			7		

typedef struct
{
	uint16_t *pBmp;			
	uint16_t BackColor;		
	uint16_t TextColor;		
}STYLE_T;

static const STYLE_T s_UI480[STYLE_COUNT] =
{
	/* ±³¾°Í¼Æ¬,		±³¾°ÑÕÉ«,			Í¼±êÎÄ×ÖÑÕÉ« */
	{0,					CL_WHITE,			CL_BLACK},	/* °×É«±³¾° */		
	{0,					RGB(0,78,152),		CL_WHITE},	/* XP×ÀÃæÀ¶±³¾° */
	{0,					RGB(185,193,204),	CL_BLACK},	/* »ÒÉ«±³¾° */	
	{0,					RGB(38,38,38),		CL_WHITE},	/* ÉîºÚÉ«±³¾° */	
	
	{(uint16_t *)(0x64000000 + 0x00200000), 0,	CL_BLACK},	/* 480x272 É³Ì²±³¾° */
	{(uint16_t *)(0x64000000 + 0x0023FC00), 0,	CL_WHITE},	/* 480x272 Ê÷Ò¶±³¾° */
	{(uint16_t *)(0x64000000 + 0x0027F800), 0,	CL_BLACK},	/* 480x272 Ë®Öé±³¾° */
};

static uint16_t s_ColorIndex = 0;

static void DispBackground(void);

uint8_t MainMenu(void)
{
    uint8_t ucKeyCode;		
	uint8_t ucTouch;		
	uint8_t fRefresh;		
    FONT_T tFont;
    FONT_T tIconFont;

    int16_t tpX, tpY;
    uint16_t i;


}

static void DispBackground(void)
{
    if (g_LcdWidth == 480)
    {
        if (s_UI480[s_ColorIndex].pBmp == 0)
        {
            LCD_ClrScr(s_UI480[s_ColorIndex].BackColor);
        }
    }
    else
    {

    }
}
