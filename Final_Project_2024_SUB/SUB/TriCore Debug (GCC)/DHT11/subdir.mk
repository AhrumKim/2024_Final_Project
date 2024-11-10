################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DHT11/DHT11.c 

C_DEPS += \
./DHT11/DHT11.d 

OBJS += \
./DHT11/DHT11.o 


# Each subdirectory must supply rules for building sources it contributes
DHT11/%.o: ../DHT11/%.c DHT11/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AURIX GCC Compiler'
	tricore-elf-gcc -std=c99 "@C:/AURIX/SUB/TriCore Debug (GCC)/AURIX_GCC_Compiler-Include_paths__-I_.opt" -Og -g3 -gdwarf-3 -Wall -c -fmessage-length=0 -fno-common -fstrict-volatile-bitfields -fdata-sections -ffunction-sections -mtc161 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-DHT11

clean-DHT11:
	-$(RM) ./DHT11/DHT11.d ./DHT11/DHT11.o

.PHONY: clean-DHT11

