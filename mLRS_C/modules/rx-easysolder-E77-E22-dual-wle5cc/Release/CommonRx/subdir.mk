################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
D:/mLRS/mLRS/CommonRx/mlrs-rx.cpp \
D:/mLRS/mLRS/CommonRx/out.cpp 

OBJS += \
./CommonRx/mlrs-rx.o \
./CommonRx/out.o 

CPP_DEPS += \
./CommonRx/mlrs-rx.d \
./CommonRx/out.d 


# Each subdirectory must supply rules for building sources it contributes
CommonRx/mlrs-rx.o: D:/mLRS/mLRS/CommonRx/mlrs-rx.cpp CommonRx/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -DCORE_CM4 -DRX_DIY_E77_E22_WLE5CC -DUSE_HAL_DRIVER -DSTM32WLE5xx -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
CommonRx/out.o: D:/mLRS/mLRS/CommonRx/out.cpp CommonRx/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -DCORE_CM4 -DRX_DIY_E77_E22_WLE5CC -DUSE_HAL_DRIVER -DSTM32WLE5xx -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-CommonRx

clean-CommonRx:
	-$(RM) ./CommonRx/mlrs-rx.cyclo ./CommonRx/mlrs-rx.d ./CommonRx/mlrs-rx.o ./CommonRx/mlrs-rx.su ./CommonRx/out.cyclo ./CommonRx/out.d ./CommonRx/out.o ./CommonRx/out.su

.PHONY: clean-CommonRx

