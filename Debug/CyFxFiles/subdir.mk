################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CyFxFiles/cyfxtx.c \
../CyFxFiles/cyfxusbenumdscr.c 

S_UPPER_SRCS += \
../CyFxFiles/cyfx_gcc_startup.S 

OBJS += \
./CyFxFiles/cyfx_gcc_startup.o \
./CyFxFiles/cyfxtx.o \
./CyFxFiles/cyfxusbenumdscr.o 

C_DEPS += \
./CyFxFiles/cyfxtx.d \
./CyFxFiles/cyfxusbenumdscr.d 

S_UPPER_DEPS += \
./CyFxFiles/cyfx_gcc_startup.d 


# Each subdirectory must supply rules for building sources it contributes
CyFxFiles/%.o: ../CyFxFiles/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU Assembler'
	arm-none-eabi-gcc -mcpu=arm926ej-s -marm -mthumb-interwork -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -x assembler-with-cpp -I"C:\Program Files (x86)\Cypress\EZ-USB FX3 SDK\1.3\/fw_lib/1_3_4/inc" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

CyFxFiles/%.o: ../CyFxFiles/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=arm926ej-s -marm -mthumb-interwork -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -D__CYU3P_TX__=1 -I"C:\Program Files (x86)\Cypress\EZ-USB FX3 SDK\1.3\/fw_lib/1_3_4/inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


