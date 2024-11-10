################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LED_BUZZER/LED_BUZZER.c 

C_DEPS += \
./LED_BUZZER/LED_BUZZER.d 

OBJS += \
./LED_BUZZER/LED_BUZZER.o 


# Each subdirectory must supply rules for building sources it contributes
LED_BUZZER/%.o: ../LED_BUZZER/%.c LED_BUZZER/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AURIX GCC Compiler'
	tricore-elf-gcc -std=c99 "@C:/Users/FM17/AURIX-v1.10.2-workspace/Team_Project/TriCore Debug (GCC)/AURIX_GCC_Compiler-Include_paths__-I_.opt" -Og -g3 -gdwarf-3 -Wall -c -fmessage-length=0 -fno-common -fstrict-volatile-bitfields -fdata-sections -ffunction-sections -mtc161 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-LED_BUZZER

clean-LED_BUZZER:
	-$(RM) ./LED_BUZZER/LED_BUZZER.d ./LED_BUZZER/LED_BUZZER.o

.PHONY: clean-LED_BUZZER

