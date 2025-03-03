/*
 * bsp.h
 *
 *  Created on: Feb 27, 2025
 *      Author: compro
 */

#ifndef BSP_BSP_H_
#define BSP_BSP_H_

#define STM32_V5
//#define STM32_X3

#if !defined (STM32_V5) && !defined (STM32_X3)
	#error "Please define the board model : STM32_X3 or STM32_V5"
#endif

#define __STM32F1_BSP_VERSION		"1.1"

//#define CPU_IDLE()		bsp_Idle()

#define ENABLE_INT()	__set_PRIMASK(0)
#define DISABLE_INT()	__set_PRIMASK(1)

#define BSP_Printf		printf
//#define BSP_Printf(...)

#include "main.h"
#include <stdio.h>
#include <string.h>

#ifndef TRUE
	#define TRUE  1
#endif

#ifndef FALSE
	#define FALSE 0
#endif

#define DEBUG_GPS_TO_COM1	/* ´òÓ¡GPSÊý¾Ýµ½´®¿Ú1 */

#include "bsp_tft_lcd.h"
#include "LCD_RA8875.h"
#include "bsp_ra8875_port.h"
#include "LCD_SPFD5420.h"
#include "bsp_key.h"
#include "bsp_led.h"

void bsp_Init(void);
void bsp_Idle(void);

#endif /* BSP_BSP_H_ */
