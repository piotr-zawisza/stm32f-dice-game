################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/adc_drv.c \
../Core/Src/animation.c \
../Core/Src/audio.c \
../Core/Src/crc_drv.c \
../Core/Src/dice.c \
../Core/Src/main.c \
../Core/Src/pwm_drv.c \
../Core/Src/rng_utils.c \
../Core/Src/rtc_drv.c \
../Core/Src/score.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c 

OBJS += \
./Core/Src/adc_drv.o \
./Core/Src/animation.o \
./Core/Src/audio.o \
./Core/Src/crc_drv.o \
./Core/Src/dice.o \
./Core/Src/main.o \
./Core/Src/pwm_drv.o \
./Core/Src/rng_utils.o \
./Core/Src/rtc_drv.o \
./Core/Src/score.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o 

C_DEPS += \
./Core/Src/adc_drv.d \
./Core/Src/animation.d \
./Core/Src/audio.d \
./Core/Src/crc_drv.d \
./Core/Src/dice.d \
./Core/Src/main.d \
./Core/Src/pwm_drv.d \
./Core/Src/rng_utils.d \
./Core/Src/rtc_drv.d \
./Core/Src/score.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/BSP/STM32F429I-Discovery -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/adc_drv.cyclo ./Core/Src/adc_drv.d ./Core/Src/adc_drv.o ./Core/Src/adc_drv.su ./Core/Src/animation.cyclo ./Core/Src/animation.d ./Core/Src/animation.o ./Core/Src/animation.su ./Core/Src/audio.cyclo ./Core/Src/audio.d ./Core/Src/audio.o ./Core/Src/audio.su ./Core/Src/crc_drv.cyclo ./Core/Src/crc_drv.d ./Core/Src/crc_drv.o ./Core/Src/crc_drv.su ./Core/Src/dice.cyclo ./Core/Src/dice.d ./Core/Src/dice.o ./Core/Src/dice.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/pwm_drv.cyclo ./Core/Src/pwm_drv.d ./Core/Src/pwm_drv.o ./Core/Src/pwm_drv.su ./Core/Src/rng_utils.cyclo ./Core/Src/rng_utils.d ./Core/Src/rng_utils.o ./Core/Src/rng_utils.su ./Core/Src/rtc_drv.cyclo ./Core/Src/rtc_drv.d ./Core/Src/rtc_drv.o ./Core/Src/rtc_drv.su ./Core/Src/score.cyclo ./Core/Src/score.d ./Core/Src/score.o ./Core/Src/score.su ./Core/Src/stm32f4xx_hal_msp.cyclo ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_it.cyclo ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.cyclo ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su

.PHONY: clean-Core-2f-Src

