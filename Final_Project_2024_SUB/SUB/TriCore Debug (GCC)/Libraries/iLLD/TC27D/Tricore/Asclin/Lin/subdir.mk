################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/iLLD/TC27D/Tricore/Asclin/Lin/IfxAsclin_Lin.c 

C_DEPS += \
./Libraries/iLLD/TC27D/Tricore/Asclin/Lin/IfxAsclin_Lin.d 

OBJS += \
./Libraries/iLLD/TC27D/Tricore/Asclin/Lin/IfxAsclin_Lin.o 


# Each subdirectory must supply rules for building sources it contributes
Libraries/iLLD/TC27D/Tricore/Asclin/Lin/%.o: ../Libraries/iLLD/TC27D/Tricore/Asclin/Lin/%.c Libraries/iLLD/TC27D/Tricore/Asclin/Lin/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AURIX GCC Compiler'
	tricore-elf-gcc -std=c99 "@C:/AURIX/SUB/TriCore Debug (GCC)/AURIX_GCC_Compiler-Include_paths__-I_.opt" -Og -g3 -gdwarf-3 -Wall -c -fmessage-length=0 -fno-common -fstrict-volatile-bitfields -fdata-sections -ffunction-sections -mtc161 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-Libraries-2f-iLLD-2f-TC27D-2f-Tricore-2f-Asclin-2f-Lin

clean-Libraries-2f-iLLD-2f-TC27D-2f-Tricore-2f-Asclin-2f-Lin:
	-$(RM) ./Libraries/iLLD/TC27D/Tricore/Asclin/Lin/IfxAsclin_Lin.d ./Libraries/iLLD/TC27D/Tricore/Asclin/Lin/IfxAsclin_Lin.o

.PHONY: clean-Libraries-2f-iLLD-2f-TC27D-2f-Tricore-2f-Asclin-2f-Lin

