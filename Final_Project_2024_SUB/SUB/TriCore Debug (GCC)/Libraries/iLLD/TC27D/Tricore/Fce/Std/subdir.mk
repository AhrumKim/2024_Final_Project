################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/iLLD/TC27D/Tricore/Fce/Std/IfxFce.c 

C_DEPS += \
./Libraries/iLLD/TC27D/Tricore/Fce/Std/IfxFce.d 

OBJS += \
./Libraries/iLLD/TC27D/Tricore/Fce/Std/IfxFce.o 


# Each subdirectory must supply rules for building sources it contributes
Libraries/iLLD/TC27D/Tricore/Fce/Std/%.o: ../Libraries/iLLD/TC27D/Tricore/Fce/Std/%.c Libraries/iLLD/TC27D/Tricore/Fce/Std/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AURIX GCC Compiler'
	tricore-elf-gcc -std=c99 "@C:/AURIX/SUB/TriCore Debug (GCC)/AURIX_GCC_Compiler-Include_paths__-I_.opt" -Og -g3 -gdwarf-3 -Wall -c -fmessage-length=0 -fno-common -fstrict-volatile-bitfields -fdata-sections -ffunction-sections -mtc161 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-Libraries-2f-iLLD-2f-TC27D-2f-Tricore-2f-Fce-2f-Std

clean-Libraries-2f-iLLD-2f-TC27D-2f-Tricore-2f-Fce-2f-Std:
	-$(RM) ./Libraries/iLLD/TC27D/Tricore/Fce/Std/IfxFce.d ./Libraries/iLLD/TC27D/Tricore/Fce/Std/IfxFce.o

.PHONY: clean-Libraries-2f-iLLD-2f-TC27D-2f-Tricore-2f-Fce-2f-Std
