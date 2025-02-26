/*
 * fonts.h
 *
 *  Created on: Feb 26, 2025
 *      Author: compro
 */

#ifndef INC_FONTS_H_
#define INC_FONTS_H_

extern unsigned char const g_Ascii16[];
extern unsigned char const g_Hz16[];
extern unsigned char const g_Ascii12[];
extern unsigned char const g_Hz12[];

//#define USE_SMALL_FONT			

/* 0x64000000 ÊÇNOR FlashµÄÊ×µØÖ· */
#define HZK12_ADDR (0x64000000 + 0x0)		
#define HZK16_ADDR (0x64000000 + 0x2C9D0)	


#endif /* INC_FONTS_H_ */
