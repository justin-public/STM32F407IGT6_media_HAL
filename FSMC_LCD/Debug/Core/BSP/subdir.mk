################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/BSP/LCD_RA8875.c \
../Core/BSP/LCD_SPFD5420.c \
../Core/BSP/bsp.c \
../Core/BSP/bsp_key.c \
../Core/BSP/bsp_led.c \
../Core/BSP/bsp_ra8875_port.c \
../Core/BSP/bsp_tft_lcd.c 

OBJS += \
./Core/BSP/LCD_RA8875.o \
./Core/BSP/LCD_SPFD5420.o \
./Core/BSP/bsp.o \
./Core/BSP/bsp_key.o \
./Core/BSP/bsp_led.o \
./Core/BSP/bsp_ra8875_port.o \
./Core/BSP/bsp_tft_lcd.o 

C_DEPS += \
./Core/BSP/LCD_RA8875.d \
./Core/BSP/LCD_SPFD5420.d \
./Core/BSP/bsp.d \
./Core/BSP/bsp_key.d \
./Core/BSP/bsp_led.d \
./Core/BSP/bsp_ra8875_port.d \
./Core/BSP/bsp_tft_lcd.d 


# Each subdirectory must supply rules for building sources it contributes
Core/BSP/%.o Core/BSP/%.su Core/BSP/%.cyclo: ../Core/BSP/%.c Core/BSP/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Core/usbh_mass_storage -I../Core/FatFS -I../Core/Fonts -I../Core/Images -I../Core/BSP -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-BSP

clean-Core-2f-BSP:
	-$(RM) ./Core/BSP/LCD_RA8875.cyclo ./Core/BSP/LCD_RA8875.d ./Core/BSP/LCD_RA8875.o ./Core/BSP/LCD_RA8875.su ./Core/BSP/LCD_SPFD5420.cyclo ./Core/BSP/LCD_SPFD5420.d ./Core/BSP/LCD_SPFD5420.o ./Core/BSP/LCD_SPFD5420.su ./Core/BSP/bsp.cyclo ./Core/BSP/bsp.d ./Core/BSP/bsp.o ./Core/BSP/bsp.su ./Core/BSP/bsp_key.cyclo ./Core/BSP/bsp_key.d ./Core/BSP/bsp_key.o ./Core/BSP/bsp_key.su ./Core/BSP/bsp_led.cyclo ./Core/BSP/bsp_led.d ./Core/BSP/bsp_led.o ./Core/BSP/bsp_led.su ./Core/BSP/bsp_ra8875_port.cyclo ./Core/BSP/bsp_ra8875_port.d ./Core/BSP/bsp_ra8875_port.o ./Core/BSP/bsp_ra8875_port.su ./Core/BSP/bsp_tft_lcd.cyclo ./Core/BSP/bsp_tft_lcd.d ./Core/BSP/bsp_tft_lcd.o ./Core/BSP/bsp_tft_lcd.su

.PHONY: clean-Core-2f-BSP

