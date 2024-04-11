################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
D:/mLRS/mLRS/Common/channel_order.cpp \
D:/mLRS/mLRS/Common/common_types.cpp \
D:/mLRS/mLRS/Common/diversity.cpp \
D:/mLRS/mLRS/Common/fhss.cpp \
D:/mLRS/mLRS/Common/link_types.cpp \
D:/mLRS/mLRS/Common/while.cpp 

OBJS += \
./Common/channel_order.o \
./Common/common_types.o \
./Common/diversity.o \
./Common/fhss.o \
./Common/link_types.o \
./Common/while.o 

CPP_DEPS += \
./Common/channel_order.d \
./Common/common_types.d \
./Common/diversity.d \
./Common/fhss.d \
./Common/link_types.d \
./Common/while.d 


# Each subdirectory must supply rules for building sources it contributes
Common/channel_order.o: D:/mLRS/mLRS/Common/channel_order.cpp Common/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -DUSE_FULL_LL_DRIVER -DTX_DIY_E77_E22_WLE5CC -c -I../Core/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Common/common_types.o: D:/mLRS/mLRS/Common/common_types.cpp Common/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -DUSE_FULL_LL_DRIVER -DTX_DIY_E77_E22_WLE5CC -c -I../Core/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Common/diversity.o: D:/mLRS/mLRS/Common/diversity.cpp Common/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -DUSE_FULL_LL_DRIVER -DTX_DIY_E77_E22_WLE5CC -c -I../Core/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Common/fhss.o: D:/mLRS/mLRS/Common/fhss.cpp Common/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -DUSE_FULL_LL_DRIVER -DTX_DIY_E77_E22_WLE5CC -c -I../Core/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Common/link_types.o: D:/mLRS/mLRS/Common/link_types.cpp Common/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -DUSE_FULL_LL_DRIVER -DTX_DIY_E77_E22_WLE5CC -c -I../Core/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Common/while.o: D:/mLRS/mLRS/Common/while.cpp Common/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -DUSE_FULL_LL_DRIVER -DTX_DIY_E77_E22_WLE5CC -c -I../Core/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Common

clean-Common:
	-$(RM) ./Common/channel_order.cyclo ./Common/channel_order.d ./Common/channel_order.o ./Common/channel_order.su ./Common/common_types.cyclo ./Common/common_types.d ./Common/common_types.o ./Common/common_types.su ./Common/diversity.cyclo ./Common/diversity.d ./Common/diversity.o ./Common/diversity.su ./Common/fhss.cyclo ./Common/fhss.d ./Common/fhss.o ./Common/fhss.su ./Common/link_types.cyclo ./Common/link_types.d ./Common/link_types.o ./Common/link_types.su ./Common/while.cyclo ./Common/while.d ./Common/while.o ./Common/while.su

.PHONY: clean-Common

