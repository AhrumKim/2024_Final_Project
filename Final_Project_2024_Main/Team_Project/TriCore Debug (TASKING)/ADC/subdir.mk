################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../ADC/ADC.c" 

COMPILED_SRCS += \
"ADC/ADC.src" 

C_DEPS += \
"./ADC/ADC.d" 

OBJS += \
"ADC/ADC.o" 


# Each subdirectory must supply rules for building sources it contributes
"ADC/ADC.src":"../ADC/ADC.c" "ADC/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Users/rlaek/AURIX-v1.10.6-workspace/Final_Project_2024_Main/Team_Project/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"ADC/ADC.o":"ADC/ADC.src" "ADC/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-ADC

clean-ADC:
	-$(RM) ./ADC/ADC.d ./ADC/ADC.o ./ADC/ADC.src

.PHONY: clean-ADC

