/*
 * bsp_ra8875_port.h
 *
 *  Created on: Feb 26, 2025
 *      Author: compro
 */

#ifndef INC_BSP_RA8875_PORT_H_
#define INC_BSP_RA8875_PORT_H_

//#define RA_SOFT_SPI	   	/* Èí¼þSPI½Ó¿ÚÄ£Ê½ */
//#define RA_HARD_SPI	   	/* Ó²¼þSPI½Ó¿ÚÄ£Ê½ */
//#define RA_SOFT_8080_8	/* Èí¼þÄ£Äâ8080½Ó¿Ú,8bit */
#define RA_HARD_8080_16		/* Ó²¼þ8080½Ó¿Ú,16bit */

void RA8875_WriteCmd(uint8_t _ucRegAddr);
void RA8875_WriteData(uint8_t _ucRegValue);


#endif /* INC_BSP_RA8875_PORT_H_ */
