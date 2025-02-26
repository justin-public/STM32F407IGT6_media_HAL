/*
 * bsp.h
 *
 *  Created on: Feb 25, 2025
 *      Author: compro
 */

#ifndef INC_BSP_H_
#define INC_BSP_H_

#define STM32_V5

#if !defined (STM32_V5) && !defined (STM32_X3)
    #error "Please define the board model : STM32_X3 or STM32_V5"
#endif

#define __STM32F1_BSP_VERSION        "1.1"

#define ENABLE_INT()    __set_PRIMASK(0)    /* Enable global interrupts */
#define DISABLE_INT()   __set_PRIMASK(1)    /* Disable global interrupts */

#define BSP_Printf      printf

#include <main.h>
#include <stdio.h>
#include <string.h>

#ifndef TRUE
    #define TRUE  1
#endif

#ifndef FALSE
    #define FALSE 0
#endif

#define DEBUG_GPS_TO_COM1    /* Print GPS data to UART1 */

#include "LCD_RA8875.h"
#include "bsp_tft_lcd.h"
#include "bsp_ra8875_port.h"

/* Function prototypes */
void bsp_Init(void);
void bsp_Idle(void);

#endif /* INC_BSP_H_ */
