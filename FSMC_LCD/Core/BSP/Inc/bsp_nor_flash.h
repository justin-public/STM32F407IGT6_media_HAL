/*
 * bsp_nor_flash.h
 *
 *  Created on: Mar 5, 2025
 *      Author: compro
 */

#ifndef BSP_BSP_NOR_FLASH_H_
#define BSP_BSP_NOR_FLASH_H_

#define NOR_FLASH_ADDR  	((uint32_t)0x64000000)

typedef enum
{
	S29GL128P = 0x017E2101,
	S29GL256P = 0x017E2201,
	S29GL512P = 0x017E2301
}NOR_CHIP_ID;

uint32_t NOR_ReadID(void);

#endif /* BSP_BSP_NOR_FLASH_H_ */
