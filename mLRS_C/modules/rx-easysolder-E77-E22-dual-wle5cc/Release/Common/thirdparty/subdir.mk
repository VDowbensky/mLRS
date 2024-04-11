################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
D:/mLRS/mLRS/Common/thirdparty/thirdparty.cpp 

C_SRCS += \
D:/mLRS/mLRS/Common/thirdparty/gdisp.c 

C_DEPS += \
./Common/thirdparty/gdisp.d 

OBJS += \
./Common/thirdparty/gdisp.o \
./Common/thirdparty/thirdparty.o 

CPP_DEPS += \
./Common/thirdparty/thirdparty.d 


# Each subdirectory must supply rules for building sources it contributes
Common/thirdparty/gdisp.o: D:/mLRS/mLRS/Common/thirdparty/gdisp.c Common/thirdparty/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Common/thirdparty/thirdparty.o: D:/mLRS/mLRS/Common/thirdparty/thirdparty.cpp Common/thirdparty/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -DCORE_CM4 -DRX_DIY_E77_E22_WLE5CC -DUSE_HAL_DRIVER -DSTM32WLE5xx -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Common-2f-thirdparty

clean-Common-2f-thirdparty:
	-$(RM) ./Common/thirdparty/gdisp.cyclo ./Common/thirdparty/gdisp.d ./Common/thirdparty/gdisp.o ./Common/thirdparty/gdisp.su ./Common/thirdparty/thirdparty.cyclo ./Common/thirdparty/thirdparty.d ./Common/thirdparty/thirdparty.o ./Common/thirdparty/thirdparty.su

.PHONY: clean-Common-2f-thirdparty

