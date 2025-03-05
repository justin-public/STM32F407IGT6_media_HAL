/*
 * touch_test.c
 *
 *  Created on: Mar 4, 2025
 *      Author: compro
 */
#include "bsp.h"
#include "main_menu.h"
#include "images.h"
#include "param.h"

#define BUTTON_RET_H	32
#define BUTTON_RET_W	60
#define	BUTTON_RET_X	(g_LcdWidth - BUTTON_RET_W - 4)
#define	BUTTON_RET_Y	(g_LcdHeight - BUTTON_RET_H - 4)

void TestTouch(void)
{
    uint8_t ucKeyCode;		
	uint8_t ucTouch;		
	uint8_t fRefresh;		
	FONT_T tFont, tFontBtn;	
	char buf[64];
	uint16_t usAdcX, usAdcY;
	int16_t tpX, tpY;

    BUTTON_T tBtn;

    LCD_ClrScr(CL_BLUE);

    {
        tFont.FontCode = FC_ST_16;
        tFont.FrontColor = CL_WHITE;	
		tFont.BackColor = CL_BLUE;	
		tFont.Space = 0;				
    }
    {
        tFontBtn.FontCode = FC_ST_16;
		tFontBtn.BackColor = CL_MASK;		
		tFontBtn.FrontColor = CL_BLACK;
		tFontBtn.Space = 0;
    }
    LCD_SetBackLight(g_tParam.ucBackLight);
    
    fRefresh = 1;
    while(1)
    {
        bsp_Idle();
        if (fRefresh)
        {
            fRefresh = 0;
            {
                LCD_DispStr(5, 3, "Touchscreen Button Joystick LED Indicator Test", &tFont);
                LCD_GetChipDescribe(buf);
                sprintf(&buf[strlen(buf)], "   %d x %d", LCD_GetWidth(), LCD_GetHeight());
                LCD_DispStr(5, 23, buf, &tFont);

                if (g_ChipID == IC_8875)
                {
                    RA8875_SetFrontColor(CL_RED);
                    RA8875_SetBackColor(CL_GREEN);

                    RA8875_SetFont(RA_FONT_16, 0, 0);
                    RA8875_SetTextZoom(RA_SIZE_X1, RA_SIZE_X1);
                    RA8875_DispStr(5, 40, "RA8875 driver is working normally. OK.");
                }
                usAdcX = TOUCH_ReadAdcX();
                usAdcY = TOUCH_ReadAdcY();
                sprintf(buf, "POS X = %4d, Y = %4d   ", usAdcX, usAdcY);
                LCD_DispStr(5, 60, buf, &tFont);

                tpX = TOUCH_GetX();
                tpY = TOUCH_GetY();
                sprintf(buf, "POS  X = %4d, Y = %4d   ", tpX, tpY);
                LCD_DispStr(5, 80, buf, &tFont);

                if ((tpX > 0) && (tpY > 0))
                {
                    LCD_DrawCircle(tpX, tpY, 2, CL_YELLOW);
                }
            }
            {
                tBtn.Font = &tFontBtn;

                tBtn.Left = BUTTON_RET_X;
				tBtn.Top = BUTTON_RET_Y;
				tBtn.Height = BUTTON_RET_H;
				tBtn.Width = BUTTON_RET_W;
				tBtn.Focus = 0;	
				tBtn.pCaption = "output";
				LCD_DrawButton(&tBtn);             // <--- this
            }
        }
    }
}


