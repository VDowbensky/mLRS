################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
D:/mLRS/mLRS/Common/libs/filters.cpp 

OBJS += \
./Common/libs/filters.o 

CPP_DEPS += \
./Common/libs/filters.d 


# Each subdirectory must supply rules for building sources it contributes
Common/libs/filters.o: D:/mLRS/mLRS/Common/libs/filters.cpp Common/libs/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -DUSE_FULL_LL_DRIVER -DTX_DIY_E77_E22_WLE5CC -c -I../Core/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Common-2f-libs

clean-Common-2f-libs:
	-$(RM) ./Common/libs/filters.cyclo ./Common/libs/filters.d ./Common/libs/filters.o ./Common/libs/filters.su

.PHONY: clean-Common-2f-libs

