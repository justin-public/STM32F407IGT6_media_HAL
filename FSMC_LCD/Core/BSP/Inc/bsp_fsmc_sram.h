/*
 * bsp_fsmc_sram.h
 *
 *  Created on: Mar 5, 2025
 *      Author: compro
 */

#ifndef BSP_BSP_FSMC_SRAM_H_
#define BSP_BSP_FSMC_SRAM_H_

#define EXT_SRAM_ADDR  	((uint32_t)0x68000000)
#define EXT_SRAM_SIZE	(2 * 1024 * 1024)

uint8_t bsp_TestExtSRAM(void);

#endif /* BSP_BSP_FSMC_SRAM_H_ */
