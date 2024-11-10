################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SUB/SUB.c 

C_DEPS += \
./SUB/SUB.d 

OBJS += \
./SUB/SUB.o 


# Each subdirectory must supply rules for building sources it contributes
SUB/%.o: ../SUB/%.c SUB/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AURIX GCC Compiler'
	tricore-elf-gcc -std=c99 "@C:/AURIX/SUB/TriCore Debug (GCC)/AURIX_GCC_Compiler-Include_paths__-I_.opt" -Og -g3 -gdwarf-3 -Wall -c -fmessage-length=0 -fno-common -fstrict-volatile-bitfields -fdata-sections -ffunction-sections -mtc161 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-SUB

clean-SUB:
	-$(RM) ./SUB/SUB.d ./SUB/SUB.o

.PHONY: clean-SUB

