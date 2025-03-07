/*
 * bsp_led.c
 *
 *  Created on: Feb 28, 2025
 *      Author: compro
 */
#include "bsp.h"

#ifdef STM32_X3
    #define RCC_ALL_LED 	RCC_AHB1Periph_GPIOE	

    #define GPIO_PORT_LED1  GPIOE
    #define GPIO_PIN_LED1	GPIO_Pin_2

    #define GPIO_PORT_LED2  GPIOE
    #define GPIO_PIN_LED2	GPIO_Pin_3

    #define GPIO_PORT_LED3  GPIOE
    #define GPIO_PIN_LED3	GPIO_Pin_4

    #define GPIO_PORT_LED4  GPIOE
    #define GPIO_PIN_LED4	GPIO_Pin_5
#else   /* STM32_F4 */
    /*
		LD1     : PI10/TP_NCS          
		LD2     : PF7/NRF24L01_CSN     
		LD3     : PF8/SF_CS            
		LD4     : PC2/NRF905_CSN/VS1053_XCS  
	*/
    #define RCC_ALL_LED 	(RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOF | RCC_AHB1Periph_GPIOI)
    
    #define GPIO_PORT_LED1  GPIOI
	#define GPIO_PIN_LED1	GPIO_PIN_10

	#define GPIO_PORT_LED2  GPIOF
	#define GPIO_PIN_LED2	GPIO_PIN_7

	#define GPIO_PORT_LED3  GPIOF
	#define GPIO_PIN_LED3	GPIO_PIN_8

	#define GPIO_PORT_LED4  GPIOC
	#define GPIO_PIN_LED4	GPIO_PIN_2
#endif

void bsp_LedOn(uint8_t _no)
{
    _no--;
    if (_no == 0)
    {
        GPIO_PORT_LED1->BSRR = (GPIO_PIN_LED1 << 16);  
    }
    else if (_no == 1)
    {
        GPIO_PORT_LED2->BSRR = (GPIO_PIN_LED2 << 16);  
    }
    else if (_no == 2)
    {
        GPIO_PORT_LED3->BSRR = (GPIO_PIN_LED3 << 16);  
    }
    else if (_no == 3)
    {
        GPIO_PORT_LED4->BSRR = (GPIO_PIN_LED4 << 16);  
    }
}

void bsp_LedOff(uint8_t _no)
{
    _no--;
    if (_no == 0)
    {
        GPIO_PORT_LED1->BSRR = GPIO_PIN_LED1;  // Set bit (raise pin)
    }
    else if (_no == 1)
    {
        GPIO_PORT_LED2->BSRR = GPIO_PIN_LED2;  // Set bit (raise pin)
    }
    else if (_no == 2)
    {
        GPIO_PORT_LED3->BSRR = GPIO_PIN_LED3;  // Set bit (raise pin)
    }
    else if (_no == 3)
    {
        GPIO_PORT_LED4->BSRR = GPIO_PIN_LED4;  // Set bit (raise pin)
    }
}
