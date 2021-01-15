################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Modbus/modbus_self_implemented.c 

OBJS += \
./Modbus/modbus_self_implemented.o 

C_DEPS += \
./Modbus/modbus_self_implemented.d 


# Each subdirectory must supply rules for building sources it contributes
Modbus/%.o: ../Modbus/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=arm926ej-s -marm -mthumb-interwork -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -D__CYU3P_TX__=1 -I"C:\Program Files (x86)\Cypress\EZ-USB FX3 SDK\1.3\/fw_lib/1_3_4/inc" -I"C:\Users\soren\Workspace\BScProjectVaerksSensorInterfacing\Dependencies\libmodbus\win32" -I"C:\Users\soren\Workspace\BScProjectVaerksSensorInterfacing\Dependencies\libmodbus" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


