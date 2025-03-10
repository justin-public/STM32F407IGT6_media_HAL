/*
 * bsp_spi_flash.h
 *
 *  Created on: Mar 7, 2025
 *      Author: compro
 */

#ifndef BSP_BSP_SPI_FLASH_H_
#define BSP_BSP_SPI_FLASH_H_

enum
{
	SST25VF016B_ID = 0xBF2541,
	MX25L1606E_ID  = 0xC22015,
	W25Q64BV_ID    = 0xEF4017
};

typedef struct
{
	uint32_t ChipID;		
	char ChipName[16];		
	uint32_t TotalSize;		
	uint16_t PageSize;		
}SFLASH_T;

extern SFLASH_T g_tSF;

#endif /* BSP_BSP_SPI_FLASH_H_ */
