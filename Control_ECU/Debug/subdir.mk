################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Timer0PWM.c \
../Timer1.c \
../buzzer.c \
../dcmotor.c \
../external_eeprom.c \
../gpio.c \
../main.c \
../twi.c \
../uart.c 

OBJS += \
./Timer0PWM.o \
./Timer1.o \
./buzzer.o \
./dcmotor.o \
./external_eeprom.o \
./gpio.o \
./main.o \
./twi.o \
./uart.o 

C_DEPS += \
./Timer0PWM.d \
./Timer1.d \
./buzzer.d \
./dcmotor.d \
./external_eeprom.d \
./gpio.d \
./main.d \
./twi.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


