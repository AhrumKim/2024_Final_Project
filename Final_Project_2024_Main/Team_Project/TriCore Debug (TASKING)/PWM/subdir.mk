################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../PWM/PWM.c" 

COMPILED_SRCS += \
"PWM/PWM.src" 

C_DEPS += \
"./PWM/PWM.d" 

OBJS += \
"PWM/PWM.o" 


# Each subdirectory must supply rules for building sources it contributes
"PWM/PWM.src":"../PWM/PWM.c" "PWM/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Users/rlaek/AURIX-v1.10.6-workspace/Final_Project_2024_Main/Team_Project/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"PWM/PWM.o":"PWM/PWM.src" "PWM/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-PWM

clean-PWM:
	-$(RM) ./PWM/PWM.d ./PWM/PWM.o ./PWM/PWM.src

.PHONY: clean-PWM

