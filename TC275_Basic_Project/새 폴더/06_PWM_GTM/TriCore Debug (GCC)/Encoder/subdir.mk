################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Encoder/Encoder.c 

C_DEPS += \
./Encoder/Encoder.d 

OBJS += \
./Encoder/Encoder.o 


# Each subdirectory must supply rules for building sources it contributes
Encoder/%.o: ../Encoder/%.c Encoder/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AURIX GCC Compiler'
	tricore-elf-gcc -std=c99 "@C:/Users/FM22/AURIX-v1.10.2-workspace/06_PWM_GTM/TriCore Debug (GCC)/AURIX_GCC_Compiler-Include_paths__-I_.opt" -Og -g3 -gdwarf-3 -Wall -c -fmessage-length=0 -fno-common -fstrict-volatile-bitfields -fdata-sections -ffunction-sections -mtc161 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-Encoder

clean-Encoder:
	-$(RM) ./Encoder/Encoder.d ./Encoder/Encoder.o

.PHONY: clean-Encoder

