/*
 * bsp_tft_lcd.h
 *
 *  Created on: Feb 27, 2025
 *      Author: compro
 */

#ifndef BSP_BSP_TFT_LCD_H_
#define BSP_BSP_TFT_LCD_H_

#define RGB(R,G,B)	(((R >> 3) << 11) | ((G >> 2) << 5) | (B >> 3))	
#define RGB565_R(x)  ((x >> 8) & 0xF8)
#define RGB565_G(x)  ((x >> 3) & 0xFC)
#define RGB565_B(x)  ((x << 3) & 0xF8)
enum
{
	CL_WHITE        = RGB(255,255,255),	
	CL_BLACK        = RGB(  0,  0,  0),	
	CL_RED          = RGB(255,	0,  0),	
	CL_GREEN        = RGB(  0,255,  0),	
	CL_BLUE         = RGB(  0,	0,255),	
	CL_YELLOW       = RGB(255,255,  0),	

	CL_GREY			= RGB( 98, 98, 98), 	
	CL_GREY1		= RGB( 150, 150, 150), 	
	CL_GREY2		= RGB( 180, 180, 180), 	
	CL_GREY3		= RGB( 200, 200, 200), 	
	CL_GREY4		= RGB( 230, 230, 230), 	

	CL_BUTTON_GREY	= RGB( 220, 220, 220), 

	CL_MAGENTA      = 0xF81F,	
	CL_CYAN         = 0x7FFF,	

	CL_BLUE1        = RGB(  0,  0, 240),		
	CL_BLUE2        = RGB(  0,  0, 128),		
	CL_BLUE3        = RGB(  68, 68, 255),		
	CL_BLUE4        = RGB(  0, 64, 128),		

	CL_BTN_FACE		= RGB(236, 233, 216),	
	CL_BOX_BORDER1	= RGB(172, 168,153),	
	CL_BOX_BORDER2	= RGB(255, 255,255),	

	CL_MASK			= 0x9999	
};

enum
{
	IC_5420		= 0x5420,
	IC_4001		= 0x4001,
	IC_61509 	= 0xB509,
	IC_8875 	= 0x0075
};

typedef struct
{
    uint16_t FontCode;	
	uint16_t FrontColor;	
	uint16_t BackColor;	
	uint16_t Space;		
}FONT_T;

typedef enum
{
	FC_ST_16 = 0,		
	FC_ST_12 = 1		
}FONT_CODE_E;

typedef struct
{
	uint8_t id;
	uint16_t Left;		
	uint16_t Top;		
	uint16_t Height;	
	uint16_t Width;		
	uint16_t *pBmp;		
	char  Text[16];	
}ICON_T;

typedef enum
{
	ID_ICON		= 1,
	ID_WIN		= 2,
	ID_LABEL	= 3,
	ID_BUTTON	= 4,
	ID_CHECK 	= 5,
	ID_EDIT 	= 6,
	ID_GROUP 	= 7,
}CONTROL_ID_T;



extern uint16_t g_ChipID;			
extern uint16_t g_LcdHeight;		
extern uint16_t g_LcdWidth;			

void LCD_ClrScr(uint16_t _usColor);
void LCD_DrawBMP(uint16_t _usX, uint16_t _usY, uint16_t _usHeight, uint16_t _usWidth, uint16_t *_ptr);
uint16_t LCD_GetWidth(void);
uint16_t LCD_GetHeight(void);
uint16_t LCD_GetPixel(uint16_t _usX, uint16_t _usY);
void LCD_DrawIcon32(const ICON_T *_tIcon, FONT_T *_tFont, uint8_t _ucFocusMode);

#endif /* BSP_BSP_TFT_LCD_H_ */
