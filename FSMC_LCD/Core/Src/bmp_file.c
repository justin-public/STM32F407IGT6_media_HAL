/*
 * bmp_file.c
 *
 *  Created on: Feb 28, 2025
 *      Author: compro
 */
#include "ff.h"
#include "bmp_file.h"

__packed typedef struct
{
	uint16_t bfType;		
	uint32_t bfSize;		
	uint16_t bfReserved1;	
	uint16_t bfReserved2; 	
	uint32_t bfOffBits;		

    uint32_t biSize;		
	int32_t  biWidth;		
	int32_t  biHeight;		
	uint16_t biPlanes;		
	uint16_t biBitCount;	
	uint32_t biCompression;	
	uint32_t biSizeImage;	
	int32_t  biXPelsPerMeter;	
	int32_t  biYPelsPerMeter;	
	uint32_t biClrUsed;			
	uint32_t biClrImportant;	
}BMP_T;

static void MakeBmpHeader(__packed BMP_T *_pBmp, uint16_t _Width, uint16_t _Height)
{
    _pBmp->bfType = 0x4D42;
    _pBmp->bfSize = (_Height * _Width * 3) + 54;	
	_pBmp->bfReserved1 = 0;	
	_pBmp->bfReserved2 = 0; 
	_pBmp->bfOffBits = 54;	

	_pBmp->biSize = 40;		
	_pBmp->biWidth = _Width;
	_pBmp->biHeight = _Height;		
	_pBmp->biPlanes = 1;			
	_pBmp->biBitCount = 24;			
	_pBmp->biCompression = 0;		
	_pBmp->biSizeImage = (_Height * _Width * 3);	
	_pBmp->biXPelsPerMeter = 0;	
	_pBmp->biYPelsPerMeter = 0;	
	_pBmp->biClrUsed = 0;		
	_pBmp->biClrImportant = 0;	
}

void SaveScreenToBmp(uint16_t _index)
{
    __packed BMP_T tBmpHead;
    uint8_t LineData[800 * 3]; 	/* °´×î´ó 800ÏñËØ¿í¶È·ÖÅä»º³åÇø */
	uint16_t i,j;
	uint16_t pixel;

    FRESULT result;
	FATFS fs;
	FIL file;
	uint32_t bw;
	char path[32];
	uint8_t ucVolume = FS_SD;

    bsp_LedOn(1);
    
    MakeBmpHeader(&tBmpHead, LCD_GetWidth(), LCD_GetHeight());
    {
        result = f_mount(ucVolume, &fs);
        if(result != FR_OK)
        {
            goto quit1; 
        }
        sprintf(path, "%d:/%dx%d_%02d.bmp", ucVolume, tBmpHead.biWidth, tBmpHead.biHeight, _index);
        //result = f_opendir(&DirInf, path);
        result = f_open(&file, path, FA_CREATE_ALWAYS | FA_WRITE);
        if (result != FR_OK)
        {
            printf("%sDone (%d)\r\n", path, result);
            goto quit1;
        }
    }
    result = f_write(&file, (char *)&tBmpHead, 54, &bw);
    if (result != FR_OK)
	{
		printf("%s completed successfully\r\n", path);
		goto quit1;
	}
    for (i = 0; i <  tBmpHead.biHeight; i++)
    {
        for (j = 0; j < tBmpHead.biWidth; j++)
        {
            #if 1
			pixel = LCD_GetPixel(j, tBmpHead.biHeight - i - 1);
			LineData[3 * j + 2] = ((pixel & 0xF800) >> 8);
			LineData[3 * j + 1] = ((pixel & 0x07E0) >> 3);
			LineData[3 * j + 0] = ((pixel & 0x001F) << 3);
			#else
			if (_index == 0)
			{
				LineData[3 * j + 2] = 255;
				LineData[3 * j + 1] = 0;
				LineData[3 * j + 0] = 0;
			}
			else if (_index == 1)
			{
				LineData[3 * j + 2] = 0;
				LineData[3 * j + 1] = 255;
				LineData[3 * j + 0] = 0;
			}
			else
			{
				LineData[3 * j + 2] = 0;
				LineData[3 * j + 1] = 0;
				LineData[3 * j + 0] = 255;
			}
			#endif
        }
		#if 0
		result = f_write(&file, LineData, tBmpHead.biWidth * 3, &bw);
		if (result != FR_OK)
		{
			printf("%s File Transfer\r\n", path);
			goto quit1;
		}
		#else
		for (j = 0 ;j < tBmpHead.biWidth * 3 / 480; j++)
		{
			result = f_write(&file, &LineData[480 * j], 480, &bw);
			if (result != FR_OK)
			{
				printf("%s File Transfer\r\n", path);
				goto quit1;
			}
		}
		#endif
    }
quit1:
	f_close(&file);
	f_mount(ucVolume, NULL);
	bsp_LedOff(1);
}