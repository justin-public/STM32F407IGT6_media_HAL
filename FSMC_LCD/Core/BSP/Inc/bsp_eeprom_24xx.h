/*
 * bsp_eeprom_24xx.h
 *
 *  Created on: Mar 6, 2025
 *      Author: compro
 */

#ifndef BSP_BSP_EEPROM_24XX_H_
#define BSP_BSP_EEPROM_24XX_H_

#define AT24C128

#ifdef AT24C128
	#define EE_MODEL_NAME		"AT24C128"
	#define EE_DEV_ADDR			0xA0
	#define EE_PAGE_SIZE		64
	#define EE_SIZE				(16*1024)
	#define EE_ADDR_BYTES		2
#endif

#endif /* BSP_BSP_EEPROM_24XX_H_ */
