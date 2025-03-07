/*
 * bsp_timer.c
 *
 *  Created on: Mar 7, 2025
 *      Author: compro
 */
#include "bsp.h"

static volatile uint32_t s_uiDelayCount = 0;
static volatile uint8_t s_ucTimeOutFlag = 0;

void bsp_DelayMS(uint32_t n)
{
    if (n == 0)
	{
		return;
	}
	else if (n == 1)
	{
		n = 2;
	}
    DISABLE_INT();

    s_uiDelayCount = n;
	s_ucTimeOutFlag = 0;

    ENABLE_INT();

    while (1)
    {
        bsp_Idle();
        if (s_ucTimeOutFlag == 1)
        {
            break;
        }
    }
    
}
