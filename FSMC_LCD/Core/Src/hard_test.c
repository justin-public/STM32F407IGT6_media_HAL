/*
 * hard_test.c
 *
 *  Created on: Mar 5, 2025
 *      Author: compro
 */
#include "bsp.h"			
#include "hard_test.h"

#define BUTTON_RET_H	32
#define BUTTON_RET_W	60
#define	BUTTON_RET_X	(g_LcdWidth - BUTTON_RET_W - 4)
#define	BUTTON_RET_Y	(g_LcdHeight - BUTTON_RET_H - 4)

void HardInfo(void)
{
    uint8_t ucKeyCode;		
	uint8_t ucTouch;		
	uint8_t fRefresh;		
	FONT_T tFont, tFontBtn;	
	char buf[128];
	uint16_t x, y;
	uint16_t usLineCap = 18;

	int16_t tpX, tpY;
	BUTTON_T tBtn;

	LCD_ClrScr(CL_BLUE);
    
    {
        tFont.FontCode = FC_ST_16;
        tFont.FrontColor = CL_WHITE;	
		tFont.BackColor = CL_BLUE;	
		tFont.Space = 0;
        
        tFontBtn.FontCode = FC_ST_16;
		tFontBtn.BackColor = CL_MASK;	
		tFontBtn.FrontColor = CL_BLACK;
		tFontBtn.Space = 0;    
    }
    x = 5;
	y = 3;
	LCD_DispStr(x, y, "STM32-V5", &tFont);			
	y += usLineCap;

    {
        uint32_t CPU_Sn0, CPU_Sn1, CPU_Sn2;
        
        CPU_Sn0 = *(__IO uint32_t*)(0x1FFF7A10);
		CPU_Sn1 = *(__IO uint32_t*)(0x1FFF7A10 + 4);
		CPU_Sn2 = *(__IO uint32_t*)(0x1FFF7A10 + 8);

        printf("\r\nCPU : STM32F407IGT6, LQFP176\r\n");
        LCD_DispStr(x, y, "CPU : STM32F407IGT6, LQFP176", &tFont);
        y += usLineCap;	

        sprintf(buf, " UID = %08X %08X %08X", CPU_Sn2, CPU_Sn1, CPU_Sn0);
        printf("%s\r\n", buf);
		LCD_DispStr(x, y, buf, &tFont);
		y += usLineCap;		
    }
    {
        strcpy(buf, "TFT Driver : ");
        LCD_GetChipDescribe(&buf[strlen(buf)]);	
        sprintf(&buf[strlen(buf)], "   %d x %d", LCD_GetWidth(), LCD_GetHeight());
        LCD_DispStr(x, y, buf, &tFont);
        y += usLineCap;
    }
    {
        if (bsp_TestExtSRAM() == 0)
        {
            sprintf(buf, "SRAM Model : IS61WV102416BLL-10TL, Test OK");
            printf("%s\r\n", buf);

            LCD_DispStr(x, y, buf, &tFont);
        }
        else
        {
            sprintf(buf, "SRAM Model: IS61WV102416BLL-10TL, Test Err");
            printf("%s\r\n", buf);

            tFont.FrontColor = CL_RED;
			LCD_DispStr(x, y, buf, &tFont);
			tFont.FrontColor = CL_WHITE;
        }
        y += usLineCap;
    }
    {
        uint32_t id;
        id = NOR_ReadID();

        if (id == S29GL128P)
        {
            sprintf(buf, "NOR Flash ID = 0x%08X, Model = S29GL128P, OK", id);
            printf("%s\r\n", buf);

            LCD_DispStr(x, y, buf, &tFont);
        }
        else
        {
            sprintf(buf, "NOR Flash ID = 0x%08X, Model = xxxx, Err", id);
            printf("%s\r\n", buf);

            tFont.FrontColor = CL_RED;
            LCD_DispStr(x, y, buf, &tFont);
			tFont.FrontColor = CL_WHITE;
        }
        y += usLineCap;
    }
    {
        uint32_t id;
        
        NAND_Init();
        
        id = NAND_ReadID();

        sprintf(buf, "NAND Flash ID = 0x%04X, Type = ", id);
        if (id == HY27UF081G2A)
        {
            sprintf(buf, "NAND Flash ID = 0x%04X, Model = HY27UF081G2A, OK", id);
            printf("%s\r\n", buf);
            LCD_DispStr(x, y, buf, &tFont);
        }
        else
        {
            sprintf(buf, "NAND Flash ID = 0x%04X, Model = Unknow, Err", id);
			tFont.FrontColor = CL_RED;
			LCD_DispStr(x, y, buf, &tFont);
			tFont.FrontColor = CL_WHITE;
        }
        y += usLineCap;
    }
    {
        if (i2c_CheckDevice(EE_DEV_ADDR) == 0)
        {
        	sprintf(buf, "AT24C128 Ok (0x%02X)", EE_DEV_ADDR);
            printf("%s\r\n", buf);
            LCD_DispStr(x, y, buf, &tFont);
        }
        else
        {
            sprintf(buf, "AT24C128 Err (0x%02X)", EE_DEV_ADDR);
            printf("%s\r\n", buf);
            
            tFont.FrontColor = CL_RED;
			LCD_DispStr(x, y, buf, &tFont);
			tFont.FrontColor = CL_WHITE;
        }
        y += usLineCap;

        if (i2c_CheckDevice(I2C_ADDR_SI4730_W) == 0)
        {
            sprintf(buf, "Si4730 Ok (0x%02X)", I2C_ADDR_SI4730_W);
            printf("%s\r\n", buf);
            LCD_DispStr(x, y, buf, &tFont);
        }
        else
        {
            sprintf(buf, "Si4730 Err (0x%02X)", I2C_ADDR_SI4730_W);
            printf("%s\r\n", buf);

            tFont.FrontColor = CL_RED;
			LCD_DispStr(x, y, buf, &tFont);
			tFont.FrontColor = CL_WHITE;
        }
        y += usLineCap;

        if (i2c_CheckDevice(HMC5883L_SLAVE_ADDRESS) == 0)
        {
            sprintf(buf, "HMC5883L Ok (0x%02X)", HMC5883L_SLAVE_ADDRESS);
            printf("%s\r\n", buf);
			LCD_DispStr(x, y, buf, &tFont);
        }
        else
        {
            sprintf(buf, "HMC5883L Err (0x%02X)", HMC5883L_SLAVE_ADDRESS);
			printf("%s\r\n", buf);

            tFont.FrontColor = CL_RED;
			LCD_DispStr(x, y, buf, &tFont);
			tFont.FrontColor = CL_WHITE;
        }
        y += usLineCap;

        if (i2c_CheckDevice(MPU6050_SLAVE_ADDRESS) == 0)
        {
            sprintf(buf, "MPU6050 Ok (0x%02X)", MPU6050_SLAVE_ADDRESS);
            printf("%s\r\n", buf);
			LCD_DispStr(x, y, buf, &tFont);
        }
        else
        {
            sprintf(buf, "MPU6050 Err (0x%02X)", MPU6050_SLAVE_ADDRESS);
            printf("%s\r\n", buf);

			tFont.FrontColor = CL_RED;
			LCD_DispStr(x, y, buf, &tFont);
			tFont.FrontColor = CL_WHITE;
        }
        y += usLineCap;

        //if (i2c_CheckDevice(BMP085_SLAVE_ADDRESS) == 0)
        //{
            //sprintf(buf, "BMP085 Ok (0x%02X)", BMP085_SLAVE_ADDRESS);
			//printf("%s\r\n", buf);
			//LCD_DispStr(x, y, buf, &tFont);
        //}
        //else
        //{
            //sprintf(buf, "BMP085 Err (0x%02X)", BMP085_SLAVE_ADDRESS);
			//printf("%s\r\n", buf);

			//tFont.FrontColor = CL_RED;
			//LCD_DispStr(x, y, buf, &tFont);
			//tFont.FrontColor = CL_WHITE;
        //}
        //y += usLineCap;

        if (i2c_CheckDevice(WM8978_SLAVE_ADDRESS) == 0)
        {
            sprintf(buf, "WM8978 Ok (0x%02X)", WM8978_SLAVE_ADDRESS);
			printf("%s\r\n", buf);
			LCD_DispStr(x, y, buf, &tFont);
        }
        else
        {
            sprintf(buf, "WM8978 Err (0x%02X)", WM8978_SLAVE_ADDRESS);
			printf("%s\r\n", buf);

			tFont.FrontColor = CL_RED;
			LCD_DispStr(x, y, buf, &tFont);
			tFont.FrontColor = CL_WHITE;
        }
        y += usLineCap;
        // 2025.03.06
        if (i2c_CheckDevice(BH1750_SLAVE_ADDRESS) == 0)
        {
            sprintf(buf, "BH1750 Ok (0x%02X)", BH1750_SLAVE_ADDRESS);
            printf("%s\r\n", buf);
			LCD_DispStr(x, y, buf, &tFont);
        }
        else
        {
            sprintf(buf, "BH1750 Err (0x%02X)", BH1750_SLAVE_ADDRESS);
			printf("%s\r\n", buf);

			tFont.FrontColor = CL_RED;
			LCD_DispStr(x, y, buf, &tFont);
			tFont.FrontColor = CL_WHITE;
        }
        y += usLineCap;
    }
    {
        sprintf(buf, "SPI Flash ID= = %08X, Model = %s",g_tSF.ChipID , g_tSF.ChipName);
        printf("%s\r\n", buf);

        if(g_tSF.ChipID == W25Q64BV_ID)
        {
            LCD_DispStr(x, y, buf, &tFont);
        }
        else
        {
            tFont.FrontColor = CL_RED;
			LCD_DispStr(x, y, buf, &tFont);
			tFont.FrontColor = CL_WHITE;
        }
    }
    fRefresh = 1;	
    while(1)
    {
        bsp_Idle();

        if (fRefresh)
        {
            fRefresh = 0;
            {
				tBtn.Font = &tFontBtn;

				tBtn.Left = BUTTON_RET_X;
				tBtn.Top = BUTTON_RET_Y;
				tBtn.Height = BUTTON_RET_H;
				tBtn.Width = BUTTON_RET_W;
				tBtn.Focus = 0;	
				tBtn.pCaption = "·μ≫Ø";
				LCD_DrawButton(&tBtn);
			}
        }
        ucTouch = TOUCH_GetKey(&tpX, &tpY);	
        if (ucTouch != TOUCH_NONE)
        {
            switch (ucTouch)
            {
                case TOUCH_DOWN:
                    if (TOUCH_InRect(tpX, tpY, BUTTON_RET_X, BUTTON_RET_Y, BUTTON_RET_H, BUTTON_RET_W))
                    {
                        tBtn.Font = &tFontBtn;

						tBtn.Left = BUTTON_RET_X;
						tBtn.Top = BUTTON_RET_Y;
						tBtn.Height = BUTTON_RET_H;
						tBtn.Width = BUTTON_RET_W;
						tBtn.Focus = 1;	
						tBtn.pCaption = "Go back";
                    }
                break;
                case TOUCH_RELEASE:
                    if (TOUCH_InRect(tpX, tpY, BUTTON_RET_X, BUTTON_RET_Y, BUTTON_RET_H, BUTTON_RET_W))
                    {
                        tBtn.Font = &tFontBtn;

						tBtn.Left = BUTTON_RET_X;
						tBtn.Top = BUTTON_RET_Y;
						tBtn.Height = BUTTON_RET_H;
						tBtn.Width = BUTTON_RET_W;
						tBtn.Focus = 1;	
						tBtn.pCaption = "Go back";
						LCD_DrawButton(&tBtn);

                        return;
                    }
                    else
                    {
                        tBtn.Font = &tFontBtn;

						tBtn.Left = BUTTON_RET_X;
						tBtn.Top = BUTTON_RET_Y;
						tBtn.Height = BUTTON_RET_H;
						tBtn.Width = BUTTON_RET_W;
						tBtn.Focus = 0;	
						tBtn.pCaption = "Go back";
						LCD_DrawButton(&tBtn);
                    }
            }
        }
        ucKeyCode = bsp_GetKey();
        if (ucKeyCode != KEY_NONE)
        {
            switch (ucKeyCode)
            {
                case  JOY_DOWN_OK:		
					return;
                default:
					break;
            }
        }
    }
}
