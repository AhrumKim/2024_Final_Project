################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../Ultra/Ultra.c" 

COMPILED_SRCS += \
"Ultra/Ultra.src" 

C_DEPS += \
"./Ultra/Ultra.d" 

OBJS += \
"Ultra/Ultra.o" 


# Each subdirectory must supply rules for building sources it contributes
"Ultra/Ultra.src":"../Ultra/Ultra.c" "Ultra/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Users/rlaek/AURIX-v1.10.6-workspace/Final_Project_2024_Main/Team_Project/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"Ultra/Ultra.o":"Ultra/Ultra.src" "Ultra/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-Ultra

clean-Ultra:
	-$(RM) ./Ultra/Ultra.d ./Ultra/Ultra.o ./Ultra/Ultra.src

.PHONY: clean-Ultra

