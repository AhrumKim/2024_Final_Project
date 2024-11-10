################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CAN/CAN.c 

C_DEPS += \
./CAN/CAN.d 

OBJS += \
./CAN/CAN.o 


# Each subdirectory must supply rules for building sources it contributes
CAN/%.o: ../CAN/%.c CAN/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AURIX GCC Compiler'
	tricore-elf-gcc -std=c99 "@C:/Users/sun05/AURIX-v1.10.6-workspace/CAN/TriCore Debug (GCC)/AURIX_GCC_Compiler-Include_paths__-I_.opt" -Og -g3 -gdwarf-3 -Wall -c -fmessage-length=0 -fno-common -fstrict-volatile-bitfields -fdata-sections -ffunction-sections -mtc161 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-CAN

clean-CAN:
	-$(RM) ./CAN/CAN.d ./CAN/CAN.o

.PHONY: clean-CAN

