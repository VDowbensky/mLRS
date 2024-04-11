################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/mLRS/mLRS/modules/stm32ll-lib/src/stdstm32.c 

C_DEPS += \
./modules/stm32ll-lib/src/stdstm32.d 

OBJS += \
./modules/stm32ll-lib/src/stdstm32.o 


# Each subdirectory must supply rules for building sources it contributes
modules/stm32ll-lib/src/stdstm32.o: D:/mLRS/mLRS/modules/stm32ll-lib/src/stdstm32.c modules/stm32ll-lib/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-modules-2f-stm32ll-2d-lib-2f-src

clean-modules-2f-stm32ll-2d-lib-2f-src:
	-$(RM) ./modules/stm32ll-lib/src/stdstm32.cyclo ./modules/stm32ll-lib/src/stdstm32.d ./modules/stm32ll-lib/src/stdstm32.o ./modules/stm32ll-lib/src/stdstm32.su

.PHONY: clean-modules-2f-stm32ll-2d-lib-2f-src

