/*
 * bsp_i2c_gpio.h
 *
 *  Created on: Mar 6, 2025
 *      Author: compro
 */

#ifndef BSP_BSP_I2C_GPIO_H_
#define BSP_BSP_I2C_GPIO_H_

#define I2C_WR	0		
#define I2C_RD	1		

void i2c_Start(void);
void i2c_SendByte(uint8_t _ucByte);
uint8_t i2c_CheckDevice(uint8_t _Address);
uint8_t i2c_WaitAck(void);
void i2c_Stop(void);

#endif /* BSP_BSP_I2C_GPIO_H_ */
