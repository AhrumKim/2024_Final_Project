################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../STM/STM.c" 

COMPILED_SRCS += \
"STM/STM.src" 

C_DEPS += \
"./STM/STM.d" 

OBJS += \
"STM/STM.o" 


# Each subdirectory must supply rules for building sources it contributes
"STM/STM.src":"../STM/STM.c" "STM/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Users/rlaek/AURIX-v1.10.6-workspace/Final_Project_2024_Main/Team_Project/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"STM/STM.o":"STM/STM.src" "STM/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-STM

clean-STM:
	-$(RM) ./STM/STM.d ./STM/STM.o ./STM/STM.src

.PHONY: clean-STM

