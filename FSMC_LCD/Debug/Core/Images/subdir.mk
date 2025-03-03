################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Images/ADC.c \
../Core/Images/Camera.c \
../Core/Images/ChiLun.c \
../Core/Images/GPS.c \
../Core/Images/LCD.c \
../Core/Images/MP3.c \
../Core/Images/Phone.c \
../Core/Images/Recorder.c \
../Core/Images/USBDisk.c \
../Core/Images/Wireless.c \
../Core/Images/chujiao.c \
../Core/Images/hwinfo.c \
../Core/Images/radio.c \
../Core/Images/web.c 

OBJS += \
./Core/Images/ADC.o \
./Core/Images/Camera.o \
./Core/Images/ChiLun.o \
./Core/Images/GPS.o \
./Core/Images/LCD.o \
./Core/Images/MP3.o \
./Core/Images/Phone.o \
./Core/Images/Recorder.o \
./Core/Images/USBDisk.o \
./Core/Images/Wireless.o \
./Core/Images/chujiao.o \
./Core/Images/hwinfo.o \
./Core/Images/radio.o \
./Core/Images/web.o 

C_DEPS += \
./Core/Images/ADC.d \
./Core/Images/Camera.d \
./Core/Images/ChiLun.d \
./Core/Images/GPS.d \
./Core/Images/LCD.d \
./Core/Images/MP3.d \
./Core/Images/Phone.d \
./Core/Images/Recorder.d \
./Core/Images/USBDisk.d \
./Core/Images/Wireless.d \
./Core/Images/chujiao.d \
./Core/Images/hwinfo.d \
./Core/Images/radio.d \
./Core/Images/web.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Images/%.o Core/Images/%.su Core/Images/%.cyclo: ../Core/Images/%.c Core/Images/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Core/usbh_mass_storage -I../Core/FatFS -I../Core/Fonts -I../Core/Images -I../Core/BSP -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Images

clean-Core-2f-Images:
	-$(RM) ./Core/Images/ADC.cyclo ./Core/Images/ADC.d ./Core/Images/ADC.o ./Core/Images/ADC.su ./Core/Images/Camera.cyclo ./Core/Images/Camera.d ./Core/Images/Camera.o ./Core/Images/Camera.su ./Core/Images/ChiLun.cyclo ./Core/Images/ChiLun.d ./Core/Images/ChiLun.o ./Core/Images/ChiLun.su ./Core/Images/GPS.cyclo ./Core/Images/GPS.d ./Core/Images/GPS.o ./Core/Images/GPS.su ./Core/Images/LCD.cyclo ./Core/Images/LCD.d ./Core/Images/LCD.o ./Core/Images/LCD.su ./Core/Images/MP3.cyclo ./Core/Images/MP3.d ./Core/Images/MP3.o ./Core/Images/MP3.su ./Core/Images/Phone.cyclo ./Core/Images/Phone.d ./Core/Images/Phone.o ./Core/Images/Phone.su ./Core/Images/Recorder.cyclo ./Core/Images/Recorder.d ./Core/Images/Recorder.o ./Core/Images/Recorder.su ./Core/Images/USBDisk.cyclo ./Core/Images/USBDisk.d ./Core/Images/USBDisk.o ./Core/Images/USBDisk.su ./Core/Images/Wireless.cyclo ./Core/Images/Wireless.d ./Core/Images/Wireless.o ./Core/Images/Wireless.su ./Core/Images/chujiao.cyclo ./Core/Images/chujiao.d ./Core/Images/chujiao.o ./Core/Images/chujiao.su ./Core/Images/hwinfo.cyclo ./Core/Images/hwinfo.d ./Core/Images/hwinfo.o ./Core/Images/hwinfo.su ./Core/Images/radio.cyclo ./Core/Images/radio.d ./Core/Images/radio.o ./Core/Images/radio.su ./Core/Images/web.cyclo ./Core/Images/web.d ./Core/Images/web.o ./Core/Images/web.su

.PHONY: clean-Core-2f-Images

