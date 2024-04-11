################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
D:/mLRS/mLRS/CommonTx/config_id.cpp \
D:/mLRS/mLRS/CommonTx/in.cpp \
D:/mLRS/mLRS/CommonTx/mlrs-tx.cpp 

OBJS += \
./CommonTx/config_id.o \
./CommonTx/in.o \
./CommonTx/mlrs-tx.o 

CPP_DEPS += \
./CommonTx/config_id.d \
./CommonTx/in.d \
./CommonTx/mlrs-tx.d 


# Each subdirectory must supply rules for building sources it contributes
CommonTx/config_id.o: D:/mLRS/mLRS/CommonTx/config_id.cpp CommonTx/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -DUSE_FULL_LL_DRIVER -DTX_DIY_E77_E22_WLE5CC -c -I../Core/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
CommonTx/in.o: D:/mLRS/mLRS/CommonTx/in.cpp CommonTx/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -DUSE_FULL_LL_DRIVER -DTX_DIY_E77_E22_WLE5CC -c -I../Core/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
CommonTx/mlrs-tx.o: D:/mLRS/mLRS/CommonTx/mlrs-tx.cpp CommonTx/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -DUSE_FULL_LL_DRIVER -DTX_DIY_E77_E22_WLE5CC -c -I../Core/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-CommonTx

clean-CommonTx:
	-$(RM) ./CommonTx/config_id.cyclo ./CommonTx/config_id.d ./CommonTx/config_id.o ./CommonTx/config_id.su ./CommonTx/in.cyclo ./CommonTx/in.d ./CommonTx/in.o ./CommonTx/in.su ./CommonTx/mlrs-tx.cyclo ./CommonTx/mlrs-tx.d ./CommonTx/mlrs-tx.o ./CommonTx/mlrs-tx.su

.PHONY: clean-CommonTx

