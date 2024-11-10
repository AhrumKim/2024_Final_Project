################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GPIO/GPIO.c 

C_DEPS += \
./GPIO/GPIO.d 

OBJS += \
./GPIO/GPIO.o 


# Each subdirectory must supply rules for building sources it contributes
GPIO/%.o: ../GPIO/%.c GPIO/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AURIX GCC Compiler'
	tricore-elf-gcc -std=c99 "@C:/Users/sun05/AURIX-v1.10.6-workspace/GPIO/TriCore Debug (GCC)/AURIX_GCC_Compiler-Include_paths__-I_.opt" -Og -g3 -gdwarf-3 -Wall -c -fmessage-length=0 -fno-common -fstrict-volatile-bitfields -fdata-sections -ffunction-sections -mtc161 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-GPIO

clean-GPIO:
	-$(RM) ./GPIO/GPIO.d ./GPIO/GPIO.o

.PHONY: clean-GPIO

