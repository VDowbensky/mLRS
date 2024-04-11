################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
D:/mLRS/mLRS/modules/sx12xx-lib/src/sx126x.cpp \
D:/mLRS/mLRS/modules/sx12xx-lib/src/sx127x.cpp \
D:/mLRS/mLRS/modules/sx12xx-lib/src/sx128x.cpp 

OBJS += \
./modules/sx12xx-lib/src/sx126x.o \
./modules/sx12xx-lib/src/sx127x.o \
./modules/sx12xx-lib/src/sx128x.o 

CPP_DEPS += \
./modules/sx12xx-lib/src/sx126x.d \
./modules/sx12xx-lib/src/sx127x.d \
./modules/sx12xx-lib/src/sx128x.d 


# Each subdirectory must supply rules for building sources it contributes
modules/sx12xx-lib/src/sx126x.o: D:/mLRS/mLRS/modules/sx12xx-lib/src/sx126x.cpp modules/sx12xx-lib/src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -DUSE_FULL_LL_DRIVER -DTX_DIY_E77_E22_WLE5CC -c -I../Core/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
modules/sx12xx-lib/src/sx127x.o: D:/mLRS/mLRS/modules/sx12xx-lib/src/sx127x.cpp modules/sx12xx-lib/src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -DUSE_FULL_LL_DRIVER -DTX_DIY_E77_E22_WLE5CC -c -I../Core/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
modules/sx12xx-lib/src/sx128x.o: D:/mLRS/mLRS/modules/sx12xx-lib/src/sx128x.cpp modules/sx12xx-lib/src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -DUSE_FULL_LL_DRIVER -DTX_DIY_E77_E22_WLE5CC -c -I../Core/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-modules-2f-sx12xx-2d-lib-2f-src

clean-modules-2f-sx12xx-2d-lib-2f-src:
	-$(RM) ./modules/sx12xx-lib/src/sx126x.cyclo ./modules/sx12xx-lib/src/sx126x.d ./modules/sx12xx-lib/src/sx126x.o ./modules/sx12xx-lib/src/sx126x.su ./modules/sx12xx-lib/src/sx127x.cyclo ./modules/sx12xx-lib/src/sx127x.d ./modules/sx12xx-lib/src/sx127x.o ./modules/sx12xx-lib/src/sx127x.su ./modules/sx12xx-lib/src/sx128x.cyclo ./modules/sx12xx-lib/src/sx128x.d ./modules/sx12xx-lib/src/sx128x.o ./modules/sx12xx-lib/src/sx128x.su

.PHONY: clean-modules-2f-sx12xx-2d-lib-2f-src

