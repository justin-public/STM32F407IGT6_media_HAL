/*
 * bsp_nor_flash.c
 *
 *  Created on: Mar 5, 2025
 *      Author: compro
 */
#include "bsp.h"

#define ADDR_SHIFT(A) 	(NOR_FLASH_ADDR + (2 * (A)))
#define NOR_WRITE(Address, Data)  (*(__IO uint16_t *)(Address) = (Data))

uint32_t NOR_ReadID(void)
{
    uint32_t uiID;
	uint8_t id1, id2, id3, id4;

    NOR_WRITE(ADDR_SHIFT(0x0555), 0x00AA);
	NOR_WRITE(ADDR_SHIFT(0x02AA), 0x0055);
	NOR_WRITE(ADDR_SHIFT(0x0555), 0x0090);

    id1 = *(__IO uint16_t *) ADDR_SHIFT(0x0000);
	id2 = *(__IO uint16_t *) ADDR_SHIFT(0x0001);
	id3 = *(__IO uint16_t *) ADDR_SHIFT(0x000E);
	id4 = *(__IO uint16_t *) ADDR_SHIFT(0x000F);

    uiID = ((uint32_t)id1 << 24) | ((uint32_t)id2 << 16)  | ((uint32_t)id3 << 8) | id4;

    NOR_WRITE(NOR_FLASH_ADDR, 0x00F0 );

    return uiID;
}