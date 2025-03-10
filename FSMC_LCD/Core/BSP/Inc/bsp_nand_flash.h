/*
 * bsp_nand_flash.h
 *
 *  Created on: Mar 6, 2025
 *      Author: compro
 */

#ifndef BSP_BSP_NAND_FLASH_H_
#define BSP_BSP_NAND_FLASH_H_



typedef enum
{
	HY27UF081G2A = 0,
	K9F1G08U0A,
	K9F1G08U0B,
	NAND_UNKNOW
}NAND_TYPE_E;

#define NAND_TYPE	HY27UF081G2A

// NAND ID
#define HY27UF081G2A	0xADF1801D

/* Exported constants --------------------------------------------------------*/
/* NAND Area definition  for STM3210E-EVAL Board RevD */
#define DATA_AREA                  ((uint32_t)0x00000000)

/* Exported functions ------------------------------------------------------- */
#define NAND_OK   0
#define NAND_FAIL 1

#define NAND_CMD_RESET             ((uint8_t)0xFF)


#define NAND_CMD_STATUS				((uint8_t)0x70)

// NAND memory status
#define NAND_ERROR                 ((uint8_t)0x01)
#define NAND_TIMEOUT_ERROR         ((uint8_t)0x80)

// FSMC NAND memory command
#define	NAND_CMD_AREA_A            ((uint8_t)0x00)
#define NAND_CMD_AREA_TRUE1        ((uint8_t)0x30)

//Intel NAND Flash has entered the 3rd generation.
#define NAND_ADDR_AREA		*(__IO uint8_t *)(Bank_NAND_ADDR | ADDR_AREA)

#define VALID_SPARE_SIZE		4

#if NAND_TYPE == HY27UF081G2A
    #define NAND_PAGE_SIZE             ((uint16_t)0x0800)
    #define NAND_BLOCK_COUNT			1024
    #define NAND_BLOCK_SIZE            ((uint16_t)0x0040) /* 64 pages per block */
    #define NAND_SPARE_AREA_SIZE       ((uint16_t)0x0040)
#else
#endif

#define BI_OFFSET		        0	
#define LBN0_OFFSET				2
#define LBN1_OFFSET				3

/*LUT = Look Up Table*/
static uint16_t s_usLUT[NAND_BLOCK_COUNT];

uint8_t NAND_Init(void);
uint32_t NAND_ReadID(void);

#endif /* BSP_BSP_NAND_FLASH_H_ */
