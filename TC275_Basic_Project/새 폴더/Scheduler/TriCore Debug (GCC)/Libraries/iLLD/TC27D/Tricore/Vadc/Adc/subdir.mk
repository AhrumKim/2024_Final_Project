################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/iLLD/TC27D/Tricore/Vadc/Adc/IfxVadc_Adc.c 

C_DEPS += \
./Libraries/iLLD/TC27D/Tricore/Vadc/Adc/IfxVadc_Adc.d 

OBJS += \
./Libraries/iLLD/TC27D/Tricore/Vadc/Adc/IfxVadc_Adc.o 


# Each subdirectory must supply rules for building sources it contributes
Libraries/iLLD/TC27D/Tricore/Vadc/Adc/%.o: ../Libraries/iLLD/TC27D/Tricore/Vadc/Adc/%.c Libraries/iLLD/TC27D/Tricore/Vadc/Adc/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AURIX GCC Compiler'
	tricore-elf-gcc -std=c99 "@C:/Users/sun05/AURIX-v1.10.6-workspace/Scheduler/TriCore Debug (GCC)/AURIX_GCC_Compiler-Include_paths__-I_.opt" -Og -g3 -gdwarf-3 -Wall -c -fmessage-length=0 -fno-common -fstrict-volatile-bitfields -fdata-sections -ffunction-sections -mtc161 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-Libraries-2f-iLLD-2f-TC27D-2f-Tricore-2f-Vadc-2f-Adc

clean-Libraries-2f-iLLD-2f-TC27D-2f-Tricore-2f-Vadc-2f-Adc:
	-$(RM) ./Libraries/iLLD/TC27D/Tricore/Vadc/Adc/IfxVadc_Adc.d ./Libraries/iLLD/TC27D/Tricore/Vadc/Adc/IfxVadc_Adc.o

.PHONY: clean-Libraries-2f-iLLD-2f-TC27D-2f-Tricore-2f-Vadc-2f-Adc

