################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/mLRS/mLRS/modules/stm32-usb-device/usbd_cdc_if.c \
D:/mLRS/mLRS/modules/stm32-usb-device/usbd_conf.c \
D:/mLRS/mLRS/modules/stm32-usb-device/usbd_desc.c 

C_DEPS += \
./modules/stm32-usb-device/usbd_cdc_if.d \
./modules/stm32-usb-device/usbd_conf.d \
./modules/stm32-usb-device/usbd_desc.d 

OBJS += \
./modules/stm32-usb-device/usbd_cdc_if.o \
./modules/stm32-usb-device/usbd_conf.o \
./modules/stm32-usb-device/usbd_desc.o 


# Each subdirectory must supply rules for building sources it contributes
modules/stm32-usb-device/usbd_cdc_if.o: D:/mLRS/mLRS/modules/stm32-usb-device/usbd_cdc_if.c modules/stm32-usb-device/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
modules/stm32-usb-device/usbd_conf.o: D:/mLRS/mLRS/modules/stm32-usb-device/usbd_conf.c modules/stm32-usb-device/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
modules/stm32-usb-device/usbd_desc.o: D:/mLRS/mLRS/modules/stm32-usb-device/usbd_desc.c modules/stm32-usb-device/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-modules-2f-stm32-2d-usb-2d-device

clean-modules-2f-stm32-2d-usb-2d-device:
	-$(RM) ./modules/stm32-usb-device/usbd_cdc_if.cyclo ./modules/stm32-usb-device/usbd_cdc_if.d ./modules/stm32-usb-device/usbd_cdc_if.o ./modules/stm32-usb-device/usbd_cdc_if.su ./modules/stm32-usb-device/usbd_conf.cyclo ./modules/stm32-usb-device/usbd_conf.d ./modules/stm32-usb-device/usbd_conf.o ./modules/stm32-usb-device/usbd_conf.su ./modules/stm32-usb-device/usbd_desc.cyclo ./modules/stm32-usb-device/usbd_desc.d ./modules/stm32-usb-device/usbd_desc.o ./modules/stm32-usb-device/usbd_desc.su

.PHONY: clean-modules-2f-stm32-2d-usb-2d-device

