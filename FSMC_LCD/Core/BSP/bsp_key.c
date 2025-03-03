/*
 * bsp_key.c
 *
 *  Created on: Feb 28, 2025
 *      Author: compro
 */
#include "bsp.h"

static KEY_FIFO_T s_tKey;

uint8_t bsp_GetKey2(void)
{
    uint8_t ret;

    if (s_tKey.Read2 == s_tKey.Write)
    {
        return KEY_NONE;
    }
    else
    {
        ret = s_tKey.Buf[s_tKey.Read2];
        if (++s_tKey.Read2 >= KEY_FIFO_SIZE)
        {
            s_tKey.Read2 = 0;
        }
        return ret;
    }
}
