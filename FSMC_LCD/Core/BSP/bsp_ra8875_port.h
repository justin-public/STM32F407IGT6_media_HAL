/*
 * bsp_ra8875_port.h
 *
 *  Created on: Feb 27, 2025
 *      Author: compro
 */

#ifndef BSP_BSP_RA8875_PORT_H_
#define BSP_BSP_RA8875_PORT_H_

//#define RA_SOFT_SPI	   	
//#define RA_HARD_SPI	   	
//#define RA_SOFT_8080_8	
#define RA_HARD_8080_16		

void RA8875_WriteCmd(uint8_t _ucRegAddr);
void RA8875_WriteData(uint8_t _ucRegValue);
uint8_t RA8875_ReadStatus(void);

#endif /* BSP_BSP_RA8875_PORT_H_ */
