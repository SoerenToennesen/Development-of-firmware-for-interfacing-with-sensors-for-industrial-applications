################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../UART/uart.c \
../UART/uart_init.c \
../UART/uart_registermode.c 

OBJS += \
./UART/uart.o \
./UART/uart_init.o \
./UART/uart_registermode.o 

C_DEPS += \
./UART/uart.d \
./UART/uart_init.d \
./UART/uart_registermode.d 


# Each subdirectory must supply rules for building sources it contributes
UART/%.o: ../UART/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=arm926ej-s -marm -mthumb-interwork -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -D__CYU3P_TX__=1 -I"C:\Program Files (x86)\Cypress\EZ-USB FX3 SDK\1.3\/fw_lib/1_3_4/inc" -I"C:\Users\soren\Workspace\BScProjectVaerksSensorInterfacing\Dependencies\libmodbus\win32" -I"C:\Users\soren\Workspace\BScProjectVaerksSensorInterfacing\Dependencies\libmodbus" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


