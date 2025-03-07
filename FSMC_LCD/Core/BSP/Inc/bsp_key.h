/*
 * bsp_key.h
 *
 *  Created on: Feb 28, 2025
 *      Author: compro
 */

#ifndef BSP_BSP_KEY_H_
#define BSP_BSP_KEY_H_

#define KEY_FIFO_SIZE	10

#define KEY_COUNT    10	   					

#define KEY_DOWN_K1		KEY_1_DOWN
#define KEY_UP_K1		KEY_1_UP
#define KEY_LONG_K1		KEY_1_LONG

#define KEY_DOWN_K2		KEY_2_DOWN
#define KEY_UP_K2		KEY_2_UP
#define KEY_LONG_K2		KEY_2_LONG

#define KEY_DOWN_K3		KEY_3_DOWN
#define KEY_UP_K3		KEY_3_UP
#define KEY_LONG_K3		KEY_3_LONG

#define JOY_DOWN_U		KEY_4_DOWN		
#define JOY_UP_U		KEY_4_UP
#define JOY_LONG_U		KEY_4_LONG

#define JOY_DOWN_D		KEY_5_DOWN		
#define JOY_UP_D		KEY_5_UP
#define JOY_LONG_D		KEY_5_LONG

#define JOY_DOWN_L		KEY_6_DOWN		
#define JOY_UP_L		KEY_6_UP
#define JOY_LONG_L		KEY_6_LONG

#define JOY_DOWN_R		KEY_7_DOWN		
#define JOY_UP_R		KEY_7_UP
#define JOY_LONG_R		KEY_7_LONG

#define JOY_DOWN_OK		KEY_8_DOWN		
#define JOY_UP_OK		KEY_8_UP
#define JOY_LONG_OK		KEY_8_LONG

#define SYS_DOWN_K1K2	KEY_9_DOWN		
#define SYS_UP_K1K2	    KEY_9_UP
#define SYS_LONG_K1K2	KEY_9_LONG

#define SYS_DOWN_K2K3	KEY_10_DOWN		
#define SYS_UP_K2K3  	KEY_10_UP
#define SYS_LONG_K2K3	KEY_10_LONG

typedef enum
{
	KEY_NONE = 0,			

	KEY_1_DOWN,				
	KEY_1_UP,				
	KEY_1_LONG,				

	KEY_2_DOWN,				
	KEY_2_UP,				
	KEY_2_LONG,				

	KEY_3_DOWN,				
	KEY_3_UP,				
	KEY_3_LONG,				

	KEY_4_DOWN,				
	KEY_4_UP,				
	KEY_4_LONG,				

	KEY_5_DOWN,				
	KEY_5_UP,				
	KEY_5_LONG,				

	KEY_6_DOWN,				
	KEY_6_UP,				
	KEY_6_LONG,				

	KEY_7_DOWN,				
	KEY_7_UP,				
	KEY_7_LONG,				

	KEY_8_DOWN,				
	KEY_8_UP,				
	KEY_8_LONG,				

	KEY_9_DOWN,				
	KEY_9_UP,				
	KEY_9_LONG,				

	KEY_10_DOWN,			
	KEY_10_UP,				
	KEY_10_LONG,			
}KEY_ENUM;

typedef struct
{
	uint8_t Buf[KEY_FIFO_SIZE];		
	uint8_t Read;					
	uint8_t Write;					
	uint8_t Read2;					
}KEY_FIFO_T;

uint8_t bsp_GetKey(void);
uint8_t bsp_GetKey2(void);

#endif /* BSP_BSP_KEY_H_ */
