/*
 * LCD_SPFD5420.c
 *
 *  Created on: Feb 27, 2025
 *      Author: compro
 */
#include "stm32f4xx.h"
#include <stdio.h>
#include <string.h>
#include "bsp_tft_lcd.h"
#include "fonts.h"

#include "stm32f4xx_hal_tim.h"


#define SPFD5420_BASE       ((uint32_t)(0x60000000 | 0x00000000))
#define SPFD5420_REG		*(__IO uint16_t *)(SPFD5420_BASE)
#define SPFD5420_RAM		*(__IO uint16_t *)(SPFD5420_BASE + (1 << 19))

static __IO uint8_t s_RGBChgEn = 0;	

static void SPFD5420_Delaly10ms(void);
static void SPFD5420_SetCursor(uint16_t _usX, uint16_t _usY);
static void SPFD5420_WriteReg(__IO uint16_t _usAddr, uint16_t _usValue);
static uint16_t SPFD5420_ReadReg(__IO uint16_t _usAddr);
static void Init_5420_4001(void);
static void Init_61509(void);

void SPFD5420_ClrScr(uint16_t _usColor)
{
    uint32_t i;
    SPFD5420_SetCursor(0, 0);
    SPFD5420_REG = 0x202;

    for (i = 0; i < g_LcdHeight * g_LcdWidth; i++)
    {
        SPFD5420_RAM = _usColor;
    }
}

static void SPFD5420_SetCursor(uint16_t _usX, uint16_t _usY)
{
    SPFD5420_WriteReg(0x0200, _usY);
    SPFD5420_WriteReg(0x0201, 399 - _usX);
}

static void SPFD5420_WriteReg(__IO uint16_t _usAddr, uint16_t _usValue)
{
    SPFD5420_REG = _usAddr;
    SPFD5420_RAM = _usValue;
}

void SPFD5420_PutPixel(uint16_t _usX, uint16_t _usY, uint16_t _usColor)
{
    SPFD5420_SetCursor(_usX, _usY);

    SPFD5420_REG = 0x202;
    SPFD5420_RAM = _usColor;
}

TIM_HandleTypeDef htim8;

void SPFD5420_SetBackLight(uint8_t _bright)
{
#if 1
    GPIO_InitTypeDef GPIO_InitStruct = {0};
	TIM_Base_InitTypeDef TIM_TimeBaseStructure = {0};
	TIM_OC_InitTypeDef TIM_OCInitStructure;
    
    __HAL_RCC_GPIOC_CLK_ENABLE();

    if (_bright == 0)
    {
    	GPIO_InitStruct.Pin = GPIO_PIN_6;
    	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    	GPIO_InitStruct.Pull = GPIO_NOPULL;

        HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

        //HAL_TIM_Base_Stop(&htim8);
        __HAL_TIM_DISABLE(&htim8);
        return;
    }
    else if(_bright == BRIGHT_MAX)
    {
        GPIO_InitStruct.Pin = GPIO_PIN_6;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.Pull = GPIO_NOPULL;

        HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);

        __HAL_TIM_DISABLE(&htim8);
        return;
    }
    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;  // Alternate Function Push-Pull
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Alternate = GPIO_AF3_TIM8;

    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
    __HAL_RCC_TIM8_CLK_ENABLE();


    htim8.Instance = TIM8;
    htim8.Init.Period = 720 - 1;
    htim8.Init.Prescaler = 0;
    htim8.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim8.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim8.Init.RepetitionCounter = 0;

    if (HAL_TIM_PWM_Init(&htim8) != HAL_OK)
    {
    	Error_Handler();
    }
    TIM_OC_InitTypeDef sConfigOC = {0};
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = (htim8.Init.Period * _bright) / BRIGHT_MAX;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;

    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;

    if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
    {
    	Error_Handler();
    }
    __HAL_TIM_ENABLE_PRELOAD(&htim8);

    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1);

    HAL_TIMEx_EnableDeadTimeBreakPreload(&htim8);
    HAL_TIMEx_EnableCommutationEvent(&htim8, TIM_COMMUTATION_SOFTWARE);
#else
    GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
    if (_bright == 0)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);

        TIM_Cmd(TIM3, DISABLE);
		return;
    }
    else if (_bright == BRIGHT_MAX)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);

		GPIO_SetBits(GPIOB, GPIO_Pin_1);

		TIM_Cmd(TIM3, DISABLE);
		return;
    }
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    TIM_TimeBaseStructure.TIM_Period = 720 - 1;	/* TIM_Period = TIM3 ARR Register */
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    /* PWM1 Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	/*
		_bright = 1 , TIM_Pulse = 1
		_bright = 255 Ê±, TIM_Pulse = TIM_Period
	*/
	TIM_OCInitStructure.TIM_Pulse = (TIM_TimeBaseStructure.TIM_Period * _bright) / BRIGHT_MAX;	

	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM3, ENABLE);
    TIM_Cmd(TIM3, ENABLE);
#endif
}

void SPFD5420_DrawCircle(uint16_t _usX, uint16_t _usY, uint16_t _usRadius, uint16_t _usColor)
{
    int32_t  D;			
	uint32_t  CurX;		
	uint32_t  CurY;		

	D = 3 - (_usRadius << 1);
	CurX = 0;
	CurY = _usRadius;

    while (CurX <= CurY)
    {
        SPFD5420_PutPixel(_usX + CurX, _usY + CurY, _usColor);
        SPFD5420_PutPixel(_usX + CurX, _usY - CurY, _usColor);
		SPFD5420_PutPixel(_usX - CurX, _usY + CurY, _usColor);
		SPFD5420_PutPixel(_usX - CurX, _usY - CurY, _usColor);
		SPFD5420_PutPixel(_usX + CurY, _usY + CurX, _usColor);
		SPFD5420_PutPixel(_usX + CurY, _usY - CurX, _usColor);
		SPFD5420_PutPixel(_usX - CurY, _usY + CurX, _usColor);
		SPFD5420_PutPixel(_usX - CurY, _usY - CurX, _usColor);

        if(D < 0)
        {
            D += (CurX << 2) + 6;
        }
        else
        {
            D += ((CurX - CurY) << 2) + 10;
            CurY--;
        }
        CurX++;
    }
}

void SPFD5420_DrawLine(uint16_t _usX1 , uint16_t _usY1 , uint16_t _usX2 , uint16_t _usY2 , uint16_t _usColor)
{
    int32_t dx , dy ;
	int32_t tx , ty ;
	int32_t inc1 , inc2 ;
	int32_t d , iTag ;
	int32_t x , y ;

    SPFD5420_PutPixel(_usX1 , _usY1 , _usColor);
    if ( _usX1 == _usX2 && _usY1 == _usY2 )
    {
        return;
    }
    iTag = 0 ;
    if (_usX2 >= _usX1)
    {
        dx = _usX2 - _usX1;
    }
    else
    {
        dx = _usX1 - _usX2;
    }
    if (_usY2 >= _usY1)
    {
        dy = _usY2 - _usY1;
    }
    else
    {
        dy = _usY1 - _usY2;
    }
    if(dx < dy)
    {
        uint16_t temp;
        
        iTag = 1;
        temp = _usX1; _usX1 = _usY1; _usY1 = temp;
		temp = _usX2; _usX2 = _usY2; _usY2 = temp;
		temp = dx; dx = dy; dy = temp;
    }
    tx = _usX2 > _usX1 ? 1 : -1 ;    
	ty = _usY2 > _usY1 ? 1 : -1 ;
	x = _usX1 ;
	y = _usY1 ;
	inc1 = 2 * dy ;
	inc2 = 2 * ( dy - dx );
	d = inc1 - dx ;
    while(x != _usX2)
    {
        if( d < 0 )
        {
            d += inc1 ;
        }
        else
        {
            y += ty;
			d += inc2;
        }
        if(iTag)
        {
            SPFD5420_PutPixel ( y , x , _usColor) ;
        }
        else
        {
            SPFD5420_PutPixel ( x , y , _usColor) ;
        }
        x += tx;
    }
}

void SPFD5420_DrawRect(uint16_t _usX, uint16_t _usY, uint8_t _usHeight, uint16_t _usWidth, uint16_t _usColor)
{
    SPFD5420_DrawLine(_usX, _usY, _usX + _usWidth - 1, _usY, _usColor);
    SPFD5420_DrawLine(_usX, _usY + _usHeight - 1, _usX + _usWidth - 1, _usY + _usHeight - 1, _usColor);
    SPFD5420_DrawLine(_usX, _usY, _usX, _usY + _usHeight - 1, _usColor);	
	SPFD5420_DrawLine(_usX + _usWidth - 1, _usY, _usX + _usWidth - 1, _usY + _usHeight, _usColor);	
}

void SPFD5420_DrawHLine(uint16_t _usX1 , uint16_t _usY1 , uint16_t _usX2 , uint16_t _usColor)
{
    uint16_t i;
    
    SPFD5420_WriteReg(0x0200, _usY1); 
    SPFD5420_WriteReg(0x0201, 399 - _usX1);

    SPFD5420_REG = 0x202;
    for (i = 0; i < _usX2 - _usX1 + 1; i++)
    {
        SPFD5420_RAM = _usColor;
    }
}

uint16_t SPFD5420_ReadID(void)
{
    return SPFD5420_ReadReg(0x0000);
}

static uint16_t SPFD5420_ReadReg(__IO uint16_t _usAddr)
{
    SPFD5420_REG = _usAddr;
    return (SPFD5420_RAM);
}

static void SPFD5420_Delaly10ms(void)
{
    uint16_t i;

	for (i = 0; i < 50000; i++);
}

static void Init_5420_4001(void)
{
    SPFD5420_WriteReg(0x0000, 0x0000);
	SPFD5420_WriteReg(0x0001, 0x0100);
	SPFD5420_WriteReg(0x0002, 0x0100);

    SPFD5420_WriteReg(0x0003, 0x1018); /* 0x1018 1030 */

	SPFD5420_WriteReg(0x0008, 0x0808);
	SPFD5420_WriteReg(0x0009, 0x0001);
	SPFD5420_WriteReg(0x000B, 0x0010);
	SPFD5420_WriteReg(0x000C, 0x0000);
	SPFD5420_WriteReg(0x000F, 0x0000);
	SPFD5420_WriteReg(0x0007, 0x0001);
	SPFD5420_WriteReg(0x0010, 0x0013);
	SPFD5420_WriteReg(0x0011, 0x0501);
	SPFD5420_WriteReg(0x0012, 0x0300);
	SPFD5420_WriteReg(0x0020, 0x021E);
	SPFD5420_WriteReg(0x0021, 0x0202);
	SPFD5420_WriteReg(0x0090, 0x8000);
	SPFD5420_WriteReg(0x0100, 0x17B0);
	SPFD5420_WriteReg(0x0101, 0x0147);
	SPFD5420_WriteReg(0x0102, 0x0135);
	SPFD5420_WriteReg(0x0103, 0x0700);
	SPFD5420_WriteReg(0x0107, 0x0000);
	SPFD5420_WriteReg(0x0110, 0x0001);
	SPFD5420_WriteReg(0x0210, 0x0000);
	SPFD5420_WriteReg(0x0211, 0x00EF);
	SPFD5420_WriteReg(0x0212, 0x0000);
	SPFD5420_WriteReg(0x0213, 0x018F);
	SPFD5420_WriteReg(0x0280, 0x0000);
	SPFD5420_WriteReg(0x0281, 0x0004);
	SPFD5420_WriteReg(0x0282, 0x0000);
	SPFD5420_WriteReg(0x0300, 0x0101);
	SPFD5420_WriteReg(0x0301, 0x0B2C);
	SPFD5420_WriteReg(0x0302, 0x1030);
	SPFD5420_WriteReg(0x0303, 0x3010);
	SPFD5420_WriteReg(0x0304, 0x2C0B);
	SPFD5420_WriteReg(0x0305, 0x0101);
	SPFD5420_WriteReg(0x0306, 0x0807);
	SPFD5420_WriteReg(0x0307, 0x0708);
	SPFD5420_WriteReg(0x0308, 0x0107);
	SPFD5420_WriteReg(0x0309, 0x0105);
	SPFD5420_WriteReg(0x030A, 0x0F04);
	SPFD5420_WriteReg(0x030B, 0x0F00);
	SPFD5420_WriteReg(0x030C, 0x000F);
	SPFD5420_WriteReg(0x030D, 0x040F);
	SPFD5420_WriteReg(0x030E, 0x0300);
	SPFD5420_WriteReg(0x030F, 0x0701);
	SPFD5420_WriteReg(0x0400, 0x3500);
	SPFD5420_WriteReg(0x0401, 0x0001);
	SPFD5420_WriteReg(0x0404, 0x0000);
	SPFD5420_WriteReg(0x0500, 0x0000);
	SPFD5420_WriteReg(0x0501, 0x0000);
	SPFD5420_WriteReg(0x0502, 0x0000);
	SPFD5420_WriteReg(0x0503, 0x0000);
	SPFD5420_WriteReg(0x0504, 0x0000);
	SPFD5420_WriteReg(0x0505, 0x0000);
	SPFD5420_WriteReg(0x0600, 0x0000);
	SPFD5420_WriteReg(0x0606, 0x0000);
	SPFD5420_WriteReg(0x06F0, 0x0000);
	SPFD5420_WriteReg(0x07F0, 0x5420);
	SPFD5420_WriteReg(0x07DE, 0x0000);
	SPFD5420_WriteReg(0x07F2, 0x00DF);
	SPFD5420_WriteReg(0x07F3, 0x0810);
	SPFD5420_WriteReg(0x07F4, 0x0077);
	SPFD5420_WriteReg(0x07F5, 0x0021);
	SPFD5420_WriteReg(0x07F0, 0x0000);
	SPFD5420_WriteReg(0x0007, 0x0173);

	SPFD5420_WriteReg(0x0210, 0);	
	SPFD5420_WriteReg(0x0211, 239);	
	SPFD5420_WriteReg(0x0212, 0);	
	SPFD5420_WriteReg(0x0213, 399);	
}

static void Init_61509(void)
{
    SPFD5420_WriteReg(0x000,0x0000);
	SPFD5420_WriteReg(0x000,0x0000);
	SPFD5420_WriteReg(0x000,0x0000);
	SPFD5420_WriteReg(0x000,0x0000);
    SPFD5420_Delaly10ms();

    SPFD5420_WriteReg(0x008,0x0808);
	SPFD5420_WriteReg(0x010,0x0010);
	SPFD5420_WriteReg(0x400,0x6200);

    SPFD5420_WriteReg(0x300,0x0c06);	/* GAMMA */
	SPFD5420_WriteReg(0x301,0x9d0f);
	SPFD5420_WriteReg(0x302,0x0b05);
	SPFD5420_WriteReg(0x303,0x1217);
	SPFD5420_WriteReg(0x304,0x3333);
	SPFD5420_WriteReg(0x305,0x1712);
	SPFD5420_WriteReg(0x306,0x950b);
	SPFD5420_WriteReg(0x307,0x0f0d);
	SPFD5420_WriteReg(0x308,0x060c);
	SPFD5420_WriteReg(0x309,0x0000);

	SPFD5420_WriteReg(0x011,0x0202);
	SPFD5420_WriteReg(0x012,0x0101);
	SPFD5420_WriteReg(0x013,0x0001);

    SPFD5420_WriteReg(0x007,0x0001);
	SPFD5420_WriteReg(0x100,0x0730);	
	SPFD5420_WriteReg(0x101,0x0237);	
	SPFD5420_WriteReg(0x103,0x2b00);	
	SPFD5420_WriteReg(0x280,0x4000);	
	SPFD5420_WriteReg(0x102,0x81b0);	
	SPFD5420_Delaly10ms();

	SPFD5420_WriteReg(0x001,0x0100);
	SPFD5420_WriteReg(0x002,0x0100);
	
	SPFD5420_WriteReg(0x003,0x1018);
	SPFD5420_WriteReg(0x009,0x0001);

	SPFD5420_WriteReg(0x0C,0x0000);	/* MCU interface  */
    /*
		SPFD5420_WriteReg(0x0C,0x0110);	//RGB interface 18bit
		SPFD5420_WriteReg(0x0C,0x0111);	//RGB interface 16bit
		SPFD5420_WriteReg(0x0C,0x0020);	//VSYNC interface
	*/
    SPFD5420_WriteReg(0x090,0x8000);
    SPFD5420_WriteReg(0x00f,0x0000);

    SPFD5420_WriteReg(0x210,0x0000);
    SPFD5420_WriteReg(0x211,0x00ef);
    SPFD5420_WriteReg(0x212,0x0000);
    SPFD5420_WriteReg(0x213,0x018f);

    SPFD5420_WriteReg(0x500,0x0000);
    SPFD5420_WriteReg(0x501,0x0000);
    SPFD5420_WriteReg(0x502,0x005f);
    SPFD5420_WriteReg(0x401,0x0001);
    SPFD5420_WriteReg(0x404,0x0000);
    SPFD5420_Delaly10ms();
    SPFD5420_WriteReg(0x007,0x0100);
    SPFD5420_Delaly10ms();
    SPFD5420_WriteReg(0x200,0x0000);
    SPFD5420_WriteReg(0x201,0x0000);
}



void SPFD5420_InitHard(void)
{
    uint16_t id;
    id = SPFD5420_ReadReg(0x0000);  	

    if ((id == 0x5420) || (id == 0x5520))	
    {
        Init_5420_4001();
        {
            uint16_t dummy;

            SPFD5420_WriteReg(0x0200, 0);
			SPFD5420_WriteReg(0x0201, 0);

            SPFD5420_REG = 0x0202;
			SPFD5420_RAM = 0x1234;

            SPFD5420_WriteReg(0x0200, 0);
			SPFD5420_WriteReg(0x0201, 0);
            SPFD5420_REG = 0x0202;
            dummy = SPFD5420_RAM;

            if (dummy == 0x1234)
            {
                s_RGBChgEn = 0;
                g_ChipID = IC_5420;
            }
            else
            {
                s_RGBChgEn = 1;		

				g_ChipID = IC_4001;
            }
            g_LcdHeight = LCD_30_HEIGHT;
			g_LcdWidth = LCD_30_WIDTH;
        }
    }
    else if(id == 0xB509)
    {
        Init_61509();		
        s_RGBChgEn = 1;			

        g_ChipID = IC_61509;
		g_LcdHeight = LCD_30_HEIGHT;
		g_LcdWidth = LCD_30_WIDTH;
    }
}

