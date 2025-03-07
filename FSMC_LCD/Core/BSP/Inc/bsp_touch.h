/*
 * bsp_touch.h
 *
 *  Created on: Mar 4, 2025
 *      Author: compro
 */

#ifndef BSP_BSP_TOUCH_H_
#define BSP_BSP_TOUCH_H_

#define CALIB_POINT_COUNT	2
#define TOUCH_FIFO_SIZE		20

typedef struct
{
	uint16_t usAdcX1;	
	uint16_t usAdcY1;

	uint16_t usAdcX2;	
	uint16_t usAdcY2;

	uint16_t usAdcX3;	
	uint16_t usAdcY3;

	uint16_t usAdcX4;	
	uint16_t usAdcY4;

	uint16_t XYChange;	

	uint16_t usMaxAdc;	
	uint16_t usAdcNowX;
	uint16_t usAdcNowY;

	uint8_t Enable;		

	uint8_t Event[TOUCH_FIFO_SIZE];	
	int16_t XBuf[TOUCH_FIFO_SIZE];	
	int16_t YBuf[TOUCH_FIFO_SIZE];	
	uint8_t Read;					
	uint8_t Write;					
}TOUCH_T;

enum
{
	TOUCH_NONE = 0,		
	TOUCH_DOWN = 1,		
	TOUCH_MOVE = 2,		
	TOUCH_RELEASE = 3	
};

int16_t TOUCH_GetX(void);
int16_t TOUCH_GetY(void);
uint8_t TOUCH_GetKey(int16_t *_pX, int16_t *_pY);
uint8_t TOUCH_InRect(uint16_t _usX, uint16_t _usY,uint16_t _usRectX, uint16_t _usRectY, uint16_t _usRectH, uint16_t _usRectW);
uint16_t TOUCH_ReadAdcX(void);
uint16_t TOUCH_ReadAdcY(void);

#endif /* BSP_BSP_TOUCH_H_ */
