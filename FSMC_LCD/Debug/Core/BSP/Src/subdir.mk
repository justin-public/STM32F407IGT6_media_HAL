################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/BSP/Src/LCD_RA8875.c \
../Core/BSP/Src/LCD_SPFD5420.c \
../Core/BSP/Src/bsp_bh1750.c \
../Core/BSP/Src/bsp_bmp085.c \
../Core/BSP/Src/bsp_eeprom_24xx.c \
../Core/BSP/Src/bsp_fsmc_sram.c \
../Core/BSP/Src/bsp_hmc5883l.c \
../Core/BSP/Src/bsp_i2c_gpio.c \
../Core/BSP/Src/bsp_key.c \
../Core/BSP/Src/bsp_led.c \
../Core/BSP/Src/bsp_mpu6050.c \
../Core/BSP/Src/bsp_nand_flash.c \
../Core/BSP/Src/bsp_nor_flash.c \
../Core/BSP/Src/bsp_ra8875_port.c \
../Core/BSP/Src/bsp_si4730.c \
../Core/BSP/Src/bsp_spi_flash.c \
../Core/BSP/Src/bsp_tft_lcd.c \
../Core/BSP/Src/bsp_timer.c \
../Core/BSP/Src/bsp_touch.c \
../Core/BSP/Src/bsp_wm8978.c 

OBJS += \
./Core/BSP/Src/LCD_RA8875.o \
./Core/BSP/Src/LCD_SPFD5420.o \
./Core/BSP/Src/bsp_bh1750.o \
./Core/BSP/Src/bsp_bmp085.o \
./Core/BSP/Src/bsp_eeprom_24xx.o \
./Core/BSP/Src/bsp_fsmc_sram.o \
./Core/BSP/Src/bsp_hmc5883l.o \
./Core/BSP/Src/bsp_i2c_gpio.o \
./Core/BSP/Src/bsp_key.o \
./Core/BSP/Src/bsp_led.o \
./Core/BSP/Src/bsp_mpu6050.o \
./Core/BSP/Src/bsp_nand_flash.o \
./Core/BSP/Src/bsp_nor_flash.o \
./Core/BSP/Src/bsp_ra8875_port.o \
./Core/BSP/Src/bsp_si4730.o \
./Core/BSP/Src/bsp_spi_flash.o \
./Core/BSP/Src/bsp_tft_lcd.o \
./Core/BSP/Src/bsp_timer.o \
./Core/BSP/Src/bsp_touch.o \
./Core/BSP/Src/bsp_wm8978.o 

C_DEPS += \
./Core/BSP/Src/LCD_RA8875.d \
./Core/BSP/Src/LCD_SPFD5420.d \
./Core/BSP/Src/bsp_bh1750.d \
./Core/BSP/Src/bsp_bmp085.d \
./Core/BSP/Src/bsp_eeprom_24xx.d \
./Core/BSP/Src/bsp_fsmc_sram.d \
./Core/BSP/Src/bsp_hmc5883l.d \
./Core/BSP/Src/bsp_i2c_gpio.d \
./Core/BSP/Src/bsp_key.d \
./Core/BSP/Src/bsp_led.d \
./Core/BSP/Src/bsp_mpu6050.d \
./Core/BSP/Src/bsp_nand_flash.d \
./Core/BSP/Src/bsp_nor_flash.d \
./Core/BSP/Src/bsp_ra8875_port.d \
./Core/BSP/Src/bsp_si4730.d \
./Core/BSP/Src/bsp_spi_flash.d \
./Core/BSP/Src/bsp_tft_lcd.d \
./Core/BSP/Src/bsp_timer.d \
./Core/BSP/Src/bsp_touch.d \
./Core/BSP/Src/bsp_wm8978.d 


# Each subdirectory must supply rules for building sources it contributes
Core/BSP/Src/%.o Core/BSP/Src/%.su Core/BSP/Src/%.cyclo: ../Core/BSP/Src/%.c Core/BSP/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Core/Src -I../Core/usbh_mass_storage -I../Core/FatFS -I../Core/Fonts -I../Core/Images -I../Core/BSP -I../Core/BSP/Inc -I../Core/BSP/Src -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-BSP-2f-Src

clean-Core-2f-BSP-2f-Src:
	-$(RM) ./Core/BSP/Src/LCD_RA8875.cyclo ./Core/BSP/Src/LCD_RA8875.d ./Core/BSP/Src/LCD_RA8875.o ./Core/BSP/Src/LCD_RA8875.su ./Core/BSP/Src/LCD_SPFD5420.cyclo ./Core/BSP/Src/LCD_SPFD5420.d ./Core/BSP/Src/LCD_SPFD5420.o ./Core/BSP/Src/LCD_SPFD5420.su ./Core/BSP/Src/bsp_bh1750.cyclo ./Core/BSP/Src/bsp_bh1750.d ./Core/BSP/Src/bsp_bh1750.o ./Core/BSP/Src/bsp_bh1750.su ./Core/BSP/Src/bsp_bmp085.cyclo ./Core/BSP/Src/bsp_bmp085.d ./Core/BSP/Src/bsp_bmp085.o ./Core/BSP/Src/bsp_bmp085.su ./Core/BSP/Src/bsp_eeprom_24xx.cyclo ./Core/BSP/Src/bsp_eeprom_24xx.d ./Core/BSP/Src/bsp_eeprom_24xx.o ./Core/BSP/Src/bsp_eeprom_24xx.su ./Core/BSP/Src/bsp_fsmc_sram.cyclo ./Core/BSP/Src/bsp_fsmc_sram.d ./Core/BSP/Src/bsp_fsmc_sram.o ./Core/BSP/Src/bsp_fsmc_sram.su ./Core/BSP/Src/bsp_hmc5883l.cyclo ./Core/BSP/Src/bsp_hmc5883l.d ./Core/BSP/Src/bsp_hmc5883l.o ./Core/BSP/Src/bsp_hmc5883l.su ./Core/BSP/Src/bsp_i2c_gpio.cyclo ./Core/BSP/Src/bsp_i2c_gpio.d ./Core/BSP/Src/bsp_i2c_gpio.o ./Core/BSP/Src/bsp_i2c_gpio.su ./Core/BSP/Src/bsp_key.cyclo ./Core/BSP/Src/bsp_key.d ./Core/BSP/Src/bsp_key.o ./Core/BSP/Src/bsp_key.su ./Core/BSP/Src/bsp_led.cyclo ./Core/BSP/Src/bsp_led.d ./Core/BSP/Src/bsp_led.o ./Core/BSP/Src/bsp_led.su ./Core/BSP/Src/bsp_mpu6050.cyclo ./Core/BSP/Src/bsp_mpu6050.d ./Core/BSP/Src/bsp_mpu6050.o ./Core/BSP/Src/bsp_mpu6050.su ./Core/BSP/Src/bsp_nand_flash.cyclo ./Core/BSP/Src/bsp_nand_flash.d ./Core/BSP/Src/bsp_nand_flash.o ./Core/BSP/Src/bsp_nand_flash.su ./Core/BSP/Src/bsp_nor_flash.cyclo ./Core/BSP/Src/bsp_nor_flash.d ./Core/BSP/Src/bsp_nor_flash.o ./Core/BSP/Src/bsp_nor_flash.su ./Core/BSP/Src/bsp_ra8875_port.cyclo ./Core/BSP/Src/bsp_ra8875_port.d ./Core/BSP/Src/bsp_ra8875_port.o ./Core/BSP/Src/bsp_ra8875_port.su ./Core/BSP/Src/bsp_si4730.cyclo ./Core/BSP/Src/bsp_si4730.d ./Core/BSP/Src/bsp_si4730.o ./Core/BSP/Src/bsp_si4730.su ./Core/BSP/Src/bsp_spi_flash.cyclo ./Core/BSP/Src/bsp_spi_flash.d ./Core/BSP/Src/bsp_spi_flash.o ./Core/BSP/Src/bsp_spi_flash.su ./Core/BSP/Src/bsp_tft_lcd.cyclo ./Core/BSP/Src/bsp_tft_lcd.d ./Core/BSP/Src/bsp_tft_lcd.o ./Core/BSP/Src/bsp_tft_lcd.su ./Core/BSP/Src/bsp_timer.cyclo ./Core/BSP/Src/bsp_timer.d ./Core/BSP/Src/bsp_timer.o ./Core/BSP/Src/bsp_timer.su ./Core/BSP/Src/bsp_touch.cyclo ./Core/BSP/Src/bsp_touch.d ./Core/BSP/Src/bsp_touch.o ./Core/BSP/Src/bsp_touch.su ./Core/BSP/Src/bsp_wm8978.cyclo ./Core/BSP/Src/bsp_wm8978.d ./Core/BSP/Src/bsp_wm8978.o ./Core/BSP/Src/bsp_wm8978.su

.PHONY: clean-Core-2f-BSP-2f-Src

