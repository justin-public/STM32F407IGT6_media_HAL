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

#define VER_INFO	"STM32-V5(V0.63)"
#define KEY_INFO	"K3K1"

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

#define ICONS_COUNT     18
static const ICON_T s_tMainIcons[ICONS_COUNT] =
{	
	{ID_ICON, ICON1_X, ICON1_Y, ICON1_H, ICON1_W, (uint16_t *)achwinfo, "achwinfo"},
	{ID_ICON, ICON2_X, ICON2_Y, ICON2_H, ICON2_W, (uint16_t *)acLCD, "acLCD"},
	{ID_ICON, ICON3_X, ICON3_Y, ICON3_H, ICON3_W, (uint16_t *)acRadio, "acRadio"},
	{ID_ICON, ICON4_X, ICON4_Y, ICON4_H, ICON4_W, (uint16_t *)acRecorder, "acRecorder"},
	{ID_ICON, ICON5_X, ICON5_Y, ICON5_H, ICON5_W, (uint16_t *)acchujiao, "MEMS"},
	{ID_ICON, ICON6_X, ICON6_Y, ICON6_H, ICON6_W, (uint16_t *)acweb, "WEB"},
	{ID_ICON, ICON7_X, ICON7_Y, ICON7_H, ICON7_W, (uint16_t *)acGPS, "GPS"},
	{ID_ICON, ICON8_X, ICON8_Y, ICON8_H, ICON8_W, (uint16_t *)acPhone, "GPRS"},
	{ID_ICON, ICON9_X, ICON9_Y, ICON9_H, ICON9_W, (uint16_t *)acMP3, "MP3"},
	{ID_ICON, ICON10_X, ICON10_Y, ICON10_H, ICON10_W, (uint16_t *)acUSBDisk, "USB"},
	{ID_ICON, ICON11_X, ICON11_Y, ICON11_H, ICON11_W, (uint16_t *)acADC, "AD7606"},	
	{ID_ICON, ICON12_X, ICON12_Y, ICON12_H, ICON12_W, (uint16_t *)acCamera, "Cam"},	
	{ID_ICON, ICON13_X, ICON13_Y, ICON13_H, ICON13_W, (uint16_t *)acChiLun, "OLED"},	
	{ID_ICON, ICON14_X, ICON14_Y, ICON14_H, ICON14_W, (uint16_t *)acWireless, "nRF24L01"},
	{ID_ICON, ICON15_X, ICON15_Y, ICON15_H, ICON15_W, (uint16_t *)acWireless, "nRF905(433M)"},	
	{ID_ICON, ICON16_X, ICON16_Y, ICON16_H, ICON16_W, (uint16_t *)acChiLun, "RS485"},	
	{ID_ICON, ICON17_X, ICON17_Y, ICON17_H, ICON17_W, (uint16_t *)acChiLun, "CAN"},	
	{ID_ICON, ICON18_X, ICON18_Y, ICON18_H, ICON18_W, (uint16_t *)acChiLun, "RA8875"},	
};



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
	
	{(uint16_t *)(0x64000000 + 0x00200000), 0,	CL_BLACK},	
	{(uint16_t *)(0x64000000 + 0x0023FC00), 0,	CL_WHITE},	
	{(uint16_t *)(0x64000000 + 0x0027F800), 0,	CL_BLACK},	
};

static const STYLE_T s_UI800[STYLE_COUNT] =
{
	{0,					CL_WHITE,			CL_BLACK},			
	{0,					RGB(0,78,152),		CL_WHITE},	
	{0,					RGB(185,193,204),	CL_BLACK},		
	{0,					RGB(38,38,38),		CL_WHITE},		
	
	{(uint16_t *)(0x64000000 + 0x002BF400), 0,	CL_BLACK},	
	{(uint16_t *)(0x64000000 + 0x0037AC00), 0,	CL_WHITE},	
	{(uint16_t *)(0x64000000 + 0x00436400), 0,	CL_BLACK},	
};

static uint16_t s_ColorIndex = 0;

#define MAIN_TEXT_COLOR		((g_LcdWidth == 480)?s_UI480[s_ColorIndex].TextColor:s_UI800[s_ColorIndex].TextColor)
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

    {
        tFont.FontCode = FC_ST_16;
        tFont.FrontColor = MAIN_TEXT_COLOR;
        tFont.BackColor = CL_MASK;
        tFont.Space = 0;

        tIconFont.FontCode = FC_ST_12;
        tIconFont.FrontColor = MAIN_TEXT_COLOR;
        tIconFont.BackColor = CL_MASK;
        tIconFont.Space = 1;
    }
    LCD_DispStr(5, 3, VER_INFO, &tFont);
    LCD_DispStr(5, g_LcdHeight - 13, KEY_INFO, &tIconFont);

    fRefresh = 1;

    while (1)
    {
        bsp_Idle();
        if (fRefresh)
        {
            fRefresh = 0;
            {
                for (i = 0; i < ICONS_COUNT; i++)
                {
                    LCD_DrawIcon32(&s_tMainIcons[i], &tIconFont, 0);
                }
            }
        }
    }
}

static void DispBackground(void)
{
    if (g_LcdWidth == 480)
    {
        if (s_UI480[s_ColorIndex].pBmp == 0)
        {
            LCD_ClrScr(s_UI480[s_ColorIndex].BackColor);
        }
        else
        {
            LCD_DrawBMP(0, 0, g_LcdHeight, g_LcdWidth, s_UI480[s_ColorIndex].pBmp);
        }
    }
    else
    {
        if (s_UI800[s_ColorIndex].pBmp == 0)
        {
            LCD_ClrScr(s_UI800[s_ColorIndex].BackColor);
        }
        else
        {
            LCD_DrawBMP(0, 0, g_LcdHeight, g_LcdWidth, s_UI800[s_ColorIndex].pBmp);
        }
    }
}
