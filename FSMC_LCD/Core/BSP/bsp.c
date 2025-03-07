/*
 * bsp.c
 *
 *  Created on: Feb 27, 2025
 *      Author: compro
 */

#include "bsp.h"

void bsp_Init(void)
{
    
}

extern void SaveScreenToBmp(uint16_t _index);
void bsp_Idle(void)
{
    if (bsp_GetKey2() == SYS_DOWN_K1K2)
    {
        static uint16_t s_file_no = 0;
        
        SaveScreenToBmp(s_file_no++);
    }
}

