################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/lcd.c \
../HAL/servo_motor.c \
../HAL/ultrasonic_timer0.c 

OBJS += \
./HAL/lcd.o \
./HAL/servo_motor.o \
./HAL/ultrasonic_timer0.o 

C_DEPS += \
./HAL/lcd.d \
./HAL/servo_motor.d \
./HAL/ultrasonic_timer0.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/%.o: ../HAL/%.c HAL/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


