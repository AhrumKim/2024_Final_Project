################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SWITCH/SWITCH.c 

C_DEPS += \
./SWITCH/SWITCH.d 

OBJS += \
./SWITCH/SWITCH.o 


# Each subdirectory must supply rules for building sources it contributes
SWITCH/%.o: ../SWITCH/%.c SWITCH/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AURIX GCC Compiler'
	tricore-elf-gcc -std=c99 "@C:/Users/FM17/AURIX-v1.10.2-workspace/Team_Project/TriCore Debug (GCC)/AURIX_GCC_Compiler-Include_paths__-I_.opt" -Og -g3 -gdwarf-3 -Wall -c -fmessage-length=0 -fno-common -fstrict-volatile-bitfields -fdata-sections -ffunction-sections -mtc161 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-SWITCH

clean-SWITCH:
	-$(RM) ./SWITCH/SWITCH.d ./SWITCH/SWITCH.o

.PHONY: clean-SWITCH

