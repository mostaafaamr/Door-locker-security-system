################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Timer1.c \
../gpio.c \
../keypad.c \
../lcd.c \
../main2.c \
../uart.c 

OBJS += \
./Timer1.o \
./gpio.o \
./keypad.o \
./lcd.o \
./main2.o \
./uart.o 

C_DEPS += \
./Timer1.d \
./gpio.d \
./keypad.d \
./lcd.d \
./main2.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


