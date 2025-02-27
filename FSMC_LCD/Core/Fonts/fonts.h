/*
 * fonts.h
 *
 *  Created on: Feb 27, 2025
 *      Author: compro
 */

#ifndef FONTS_FONTS_H_
#define FONTS_FONTS_H_

extern unsigned char const g_Ascii16[];

extern unsigned char const g_Hz16[];

extern unsigned char const g_Ascii12[];

extern unsigned char const g_Hz12[];

//#define USE_SMALL_FONT			

#define HZK12_ADDR (0x64000000 + 0x0)		
#define HZK16_ADDR (0x64000000 + 0x2C9D0)	

#endif /* FONTS_FONTS_H_ */
