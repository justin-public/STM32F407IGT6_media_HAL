/*
 * bsp_i2c_gpio.c
 *
 *  Created on: Mar 6, 2025
 *      Author: compro
 */
#include "bsp.h"

#define GPIO_PORT_I2C       GPIOH           /* GPIO port */
#define I2C_SCL_PIN         GPIO_PIN_4      /* SCL pin number */
#define I2C_SDA_PIN         GPIO_PIN_5      /* SDA pin number */

/* Set/Reset SCL and SDA pins */
#define I2C_SCL_1()  HAL_GPIO_WritePin(GPIO_PORT_I2C, I2C_SCL_PIN, GPIO_PIN_SET)    /* SCL = 1 */
#define I2C_SCL_0()  HAL_GPIO_WritePin(GPIO_PORT_I2C, I2C_SCL_PIN, GPIO_PIN_RESET)  /* SCL = 0 */
#define I2C_SDA_1()  HAL_GPIO_WritePin(GPIO_PORT_I2C, I2C_SDA_PIN, GPIO_PIN_SET)    /* SDA = 1 */
#define I2C_SDA_0()  HAL_GPIO_WritePin(GPIO_PORT_I2C, I2C_SDA_PIN, GPIO_PIN_RESET)  /* SDA = 0 */

/* Read SCL and SDA pin states */
#define I2C_SDA_READ()  (HAL_GPIO_ReadPin(GPIO_PORT_I2C, I2C_SDA_PIN) == GPIO_PIN_SET)  /* Read SDA pin state */
#define I2C_SCL_READ()  (HAL_GPIO_ReadPin(GPIO_PORT_I2C, I2C_SCL_PIN) == GPIO_PIN_SET)  /* Read SCL pin state */


static void i2c_Delay(void)
{
    uint8_t i;
    for (i = 0; i < 30; i++);
}


void i2c_Start(void)
{
    I2C_SDA_1();
	I2C_SCL_1();
    i2c_Delay();
    I2C_SDA_0();
    i2c_Delay();
    I2C_SCL_0();
    i2c_Delay();
}

void i2c_SendByte(uint8_t _ucByte)
{
    uint8_t i;

    for (i = 0; i < 8; i++)
    {
        if (_ucByte & 0x80)
        {
            I2C_SDA_1();
        }
        else
        {
            I2C_SDA_0();
        }
        i2c_Delay();
        I2C_SCL_1();
        i2c_Delay();
        I2C_SCL_0();
        if(i == 7)
        {
            I2C_SDA_1();
        }
        _ucByte <<= 1;
        i2c_Delay();
    }
}

uint8_t i2c_CheckDevice(uint8_t _Address)
{
    uint8_t ucAck;

    if (I2C_SDA_READ() && I2C_SCL_READ())
    {
        i2c_Start();
        i2c_SendByte(_Address | I2C_WR);
        ucAck = i2c_WaitAck();

        i2c_Stop();

        return ucAck;
    }
    return 1;
}

uint8_t i2c_WaitAck(void)
{
    uint8_t re;

    I2C_SDA_1();
    i2c_Delay();
    I2C_SCL_1();	
    i2c_Delay();
    if(I2C_SDA_READ())
    {
        re = 1;       
    }
    else
    {
        re = 0;
    }
    I2C_SCL_0();
    i2c_Delay();
    return re;
}

void i2c_Stop(void)
{
    I2C_SDA_0();
    I2C_SCL_1();
    i2c_Delay();
    I2C_SDA_1();
}