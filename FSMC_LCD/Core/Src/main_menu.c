/*
 * main_menu.c
 *
 *  Created on: Feb 25, 2025
 *      Author: compro
 */
#include "bsp.h"
#include "images.h"
#include "main_menu.h"
#include "main_enum.h"

#define VER_INFO	"STM32 Version 5"
#define KEY_INFO	"Key free"

#define ICON_LEFT	16
#define ICON_TOP	25

enum
{
    ICON1_X	= ICON_LEFT,
    ICON1_Y	= ICON_TOP,
    ICON1_H	= ICON_HEIGHT,
	ICON1_W	= ICON_WIDTH,

        ICON2_X	= ICON_LEFT + ICON_STEP_X,
        ICON2_Y	= ICON_TOP,
        ICON2_H	= ICON_HEIGHT,
        ICON2_W	= ICON_WIDTH,

            ICON3_X	= ICON_LEFT + 2 * ICON_STEP_X,
            ICON3_Y	= ICON_TOP,
            ICON3_H	= ICON_HEIGHT,
            ICON3_W	= ICON_WIDTH,

                ICON4_X	= ICON_LEFT + 3 * ICON_STEP_X,
                ICON4_Y	= ICON_TOP,
                ICON4_H	= ICON_HEIGHT,
                ICON4_W	= ICON_WIDTH,

                    ICON5_X	= ICON_LEFT + 4 * ICON_STEP_X,
                    ICON5_Y	= ICON_TOP,
                    ICON5_H	= ICON_HEIGHT,
                    ICON5_W	= ICON_WIDTH,

                        ICON6_X	= ICON_LEFT + 5 * ICON_STEP_X,
                        ICON6_Y	= ICON_TOP,
                        ICON6_H	= ICON_HEIGHT,
                        ICON6_W	= ICON_WIDTH,

    ICON7_X	= ICON_LEFT,
    ICON7_Y	= ICON_TOP + ICON_STEP_Y,
    ICON7_H	= ICON_HEIGHT,
    ICON7_W	= ICON_WIDTH,

        ICON8_X	= ICON_LEFT + 1 * ICON_STEP_X,
        ICON8_Y	= ICON_TOP + ICON_STEP_Y,
        ICON8_H	= ICON_HEIGHT,
        ICON8_W	= ICON_WIDTH,

            ICON9_X	= ICON_LEFT + 2 * ICON_STEP_X,
            ICON9_Y	= ICON_TOP + ICON_STEP_Y,
            ICON9_H	= ICON_HEIGHT,
            ICON9_W	= ICON_WIDTH,

                ICON10_X	= ICON_LEFT + 3 * ICON_STEP_X,
                ICON10_Y	= ICON_TOP + ICON_STEP_Y,
                ICON10_H	= ICON_HEIGHT,
                ICON10_W	= ICON_WIDTH,

                    ICON11_X	= ICON_LEFT + 4 * ICON_STEP_X,
                    ICON11_Y	= ICON_TOP + ICON_STEP_Y,
                    ICON11_H	= ICON_HEIGHT,
                    ICON11_W	= ICON_WIDTH,
                    
                        ICON12_X	= ICON_LEFT + 5 * ICON_STEP_X,
                        ICON12_Y	= ICON_TOP + ICON_STEP_Y,
                        ICON12_H	= ICON_HEIGHT,
                        ICON12_W	= ICON_WIDTH,	

    ICON13_X	= ICON_LEFT,
    ICON13_Y	= ICON_TOP + 2 * ICON_STEP_Y,
    ICON13_H	= ICON_HEIGHT,
    ICON13_W	= ICON_WIDTH,

        ICON14_X	= ICON_LEFT + 1 * ICON_STEP_X,
        ICON14_Y	= ICON_TOP + 2 * ICON_STEP_Y,
        ICON14_H	= ICON_HEIGHT,
        ICON14_W	= ICON_WIDTH,

            ICON15_X	= ICON_LEFT + 2 * ICON_STEP_X,
            ICON15_Y	= ICON_TOP + 2 * ICON_STEP_Y,
            ICON15_H	= ICON_HEIGHT,
            ICON15_W	= ICON_WIDTH,

                ICON16_X	= ICON_LEFT + 3 * ICON_STEP_X,
				ICON16_Y	= ICON_TOP + 2 * ICON_STEP_Y,
				ICON16_H	= ICON_HEIGHT,
				ICON16_W	= ICON_WIDTH,

                    ICON17_X	= ICON_LEFT + 4 * ICON_STEP_X,
					ICON17_Y	= ICON_TOP + 2 * ICON_STEP_Y,
					ICON17_H	= ICON_HEIGHT,
					ICON17_W	= ICON_WIDTH,

                        ICON18_X	= ICON_LEFT + 5 * ICON_STEP_X,
                        ICON18_Y	= ICON_TOP + 2 * ICON_STEP_Y,
                        ICON18_H	= ICON_HEIGHT,
                        ICON18_W	= ICON_WIDTH,	
};

#define STYLE_COUNT			7		

typedef struct
{
	uint16_t *pBmp;			
	uint16_t BackColor;		
	uint16_t TextColor;		
}STYLE_T;

static const STYLE_T s_UI480[STYLE_COUNT] =
{
    {0,					CL_WHITE,			CL_BLACK},
    {0,					RGB(0,78,152),		CL_WHITE},	
	{0,					RGB(185,193,204),	CL_BLACK},		
	{0,					RGB(38,38,38),		CL_WHITE},

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

    DispBackground();
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
}
