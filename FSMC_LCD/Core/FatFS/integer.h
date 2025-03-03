/*
 * integer.h
 *
 *  Created on: Feb 28, 2025
 *      Author: compro
 */

#ifndef FATFS_INTEGER_H_
#define FATFS_INTEGER_H_

//#ifdef _WIN32
    //#include <windows.h>
    //#include <tchar.h>
//#else
/* These types must be 16-bit, 32-bit or larger integer */
typedef int				INT;
typedef unsigned int	UINT;

/* These types must be 8-bit integer */
typedef char			CHAR;
typedef unsigned char	UCHAR;
typedef unsigned char	BYTE;

/* These types must be 16-bit integer */
typedef short			SHORT;
typedef unsigned short	USHORT;
typedef unsigned short	WORD;
typedef unsigned short	WCHAR;

/* These types must be 32-bit integer */
typedef long			LONG;
typedef unsigned long	ULONG;
typedef unsigned long	DWORD;
//#endif
#endif /* FATFS_INTEGER_H_ */
