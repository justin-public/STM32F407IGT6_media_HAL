/*
 * bsp_touch.c
 *
 *  Created on: Mar 4, 2025
 *      Author: compro
 */
#include "stm32f4xx.h"
#include <stdio.h>

#include "bsp_touch.h"
#include "bsp_tft_lcd.h"
#include "LCD_RA8875.h"
#include "bsp_timer.h"

#include "param.h"

TOUCH_T g_tTP;

#define CALIB_OFFSET	20
#define TP_X1	CALIB_OFFSET
#define TP_Y1	CALIB_OFFSET

#define TP_X2	(LCD_GetWidth() - CALIB_OFFSET)
#define TP_Y2	(LCD_GetHeight() - CALIB_OFFSET)

static int16_t TOUCH_TransX(uint16_t _usAdcX, uint16_t _usAdcY);
static int16_t TOUCH_TransY(uint16_t _usAdcX, uint16_t _usAdcY);
static int32_t CalTwoPoint(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x);

uint8_t TOUCH_GetKey(int16_t *_pX, int16_t *_pY)
{
    uint8_t ret;

    if(g_tTP.Read == g_tTP.Write)
    {
        return TOUCH_NONE;
    }
    else
    {
        ret = g_tTP.Event[g_tTP.Read];
		*_pX = g_tTP.XBuf[g_tTP.Read];
		*_pY = g_tTP.YBuf[g_tTP.Read];

        if (++g_tTP.Read >= TOUCH_FIFO_SIZE)
        {
            g_tTP.Read = 0;
        }
        return ret;
    }
}

uint16_t TOUCH_ReadAdcX(void)
{
    uint16_t usAdc;
    
    __set_PRIMASK(1);
    usAdc = g_tTP.usAdcNowX;
    __set_PRIMASK(0);

    return usAdc;
}

uint16_t TOUCH_ReadAdcY(void)
{
    uint16_t usAdc;

	__set_PRIMASK(1);  		
	usAdc = g_tTP.usAdcNowY;
	__set_PRIMASK(0);  		

	return usAdc;
}

static int32_t CalTwoPoint(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x)
{
    return y1 + ((int32_t)(y2 - y1) * (x - x1)) / (x2 - x1);
}

static int16_t TOUCH_TransX(uint16_t _usAdcX, uint16_t _usAdcY)
{
    #if CALIB_POINT_COUNT == 2
        uint16_t x;
	    int32_t y;

        if (g_tTP.XYChange == 0)
        {
            x = _usAdcX;
            if(x == 0)
            {
                y = 0;
            }
            else
            {
                y = CalTwoPoint(g_tTP.usAdcX1, TP_X1, g_tTP.usAdcX2, TP_X2, x);
            }
        }
        else
        {
            x = _usAdcY;
            if (x == 0)
		    {
			    y = 0;
		    }
            else
            {
                y = CalTwoPoint(g_tTP.usAdcY1, TP_X1, g_tTP.usAdcY2, TP_X2, x);
            }
        }
        return y;
    #else
        uint16_t x, x1, x2;
	    int32_t y;
        if (g_tTP.XYChange == 0)
        {
            x = _usAdcX;
            x1 = CalTwoPoint(g_tTP.usAdcY1, g_tTP.usAdcX1, g_tTP.usAdcY2,  g_tTP.usAdcX3, _usAdcY);
            x2 = CalTwoPoint(g_tTP.usAdcY1, g_tTP.usAdcX4, g_tTP.usAdcY2,  g_tTP.usAdcX2, _usAdcY);
        }
        else
        {
            x = _usAdcY;
            x1 = CalTwoPoint(g_tTP.usAdcX1, g_tTP.usAdcY1, g_tTP.usAdcX2,  g_tTP.usAdcY3, _usAdcX);
            x2 = CalTwoPoint(g_tTP.usAdcX1, g_tTP.usAdcY4, g_tTP.usAdcX2,  g_tTP.usAdcY2, _usAdcX);
        }
        if (x == 0)
	    {
		    y = 0;
	    }
	    else
	    {
		    y = CalTwoPoint(x1, TP_X1, x2, TP_X2, x);
	    }
	    return y;
    #endif
}

int16_t TOUCH_GetX(void)
{
    return TOUCH_TransX(TOUCH_ReadAdcX(), TOUCH_ReadAdcY());
}

static int16_t TOUCH_TransY(uint16_t _usAdcX, uint16_t _usAdcY)
{
    #if CALIB_POINT_COUNT == 2	
        int32_t x;
	    int32_t y;

        if (g_tTP.XYChange == 0)
        {
            x = _usAdcY;
            if(x == 0)
            {
                y = 0;
            }
            else
            {
                y = CalTwoPoint(g_tTP.usAdcY1, TP_Y1, g_tTP.usAdcY2, TP_Y2, x);
            }
        }
        else
        {
            x = _usAdcX;
            if (x == 0)
            {
                y = 0;
            }
            else
            {
                y = CalTwoPoint(g_tTP.usAdcX1, TP_Y1, g_tTP.usAdcX2, TP_Y2, x);
            }
        }
        return y;
    #else
        int32_t x, x1, x2;
	    int32_t y;
        if (g_tTP.XYChange == 0)
        {
            x = _usAdcY;
            x1 = CalTwoPoint(g_tTP.usAdcX1, g_tTP.usAdcY1, g_tTP.usAdcX2,  g_tTP.usAdcY4, _usAdcX);
		    x2 = CalTwoPoint(g_tTP.usAdcX1, g_tTP.usAdcY3, g_tTP.usAdcX2,  g_tTP.usAdcY2, _usAdcX);
        }
        else
        {
            x = _usAdcX;
            x1 = CalTwoPoint(g_tTP.usAdcY1, g_tTP.usAdcX1, g_tTP.usAdcY2,  g_tTP.usAdcX4, _usAdcY);
		    x2 = CalTwoPoint(g_tTP.usAdcY1, g_tTP.usAdcX3, g_tTP.usAdcY2,  g_tTP.usAdcX2, _usAdcY);
        }
        if (x == 0)
	    {
		    y = 0;
	    }
	    else
	    {
		    y = CalTwoPoint(x1, TP_Y1, x2, TP_Y2, x);
	    }
	    return y;
    #endif
}

int16_t TOUCH_GetY(void)
{
    return TOUCH_TransY(TOUCH_ReadAdcX(), TOUCH_ReadAdcY());
}