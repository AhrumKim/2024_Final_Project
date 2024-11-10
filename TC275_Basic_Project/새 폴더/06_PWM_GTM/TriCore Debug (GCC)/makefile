################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Scheduler/subdir.mk
-include STM/subdir.mk
-include PWM/subdir.mk
-include Libraries/iLLD/TC27D/Tricore/_PinMap/subdir.mk
-include Libraries/iLLD/TC27D/Tricore/_Lib/DataHandling/subdir.mk
-include Libraries/iLLD/TC27D/Tricore/_Impl/subdir.mk
-include Libraries/iLLD/TC27D/Tricore/Vadc/Std/subdir.mk
-include Libraries/iLLD/TC27D/Tricore/Vadc/Adc/subdir.mk
-include Libraries/iLLD/TC27D/Tricore/Stm/Std/subdir.mk
-include Libraries/iLLD/TC27D/Tricore/Src/Std/subdir.mk
-include Libraries/iLLD/TC27D/Tricore/Scu/Std/subdir.mk
-include Libraries/iLLD/TC27D/Tricore/Port/Std/subdir.mk
-include Libraries/iLLD/TC27D/Tricore/Mtu/Std/subdir.mk
-include Libraries/iLLD/TC27D/Tricore/Gtm/Tom/Timer/subdir.mk
-include Libraries/iLLD/TC27D/Tricore/Gtm/Tom/PwmHl/subdir.mk
-include Libraries/iLLD/TC27D/Tricore/Gtm/Std/subdir.mk
-include Libraries/iLLD/TC27D/Tricore/Cpu/Trap/subdir.mk
-include Libraries/iLLD/TC27D/Tricore/Cpu/Std/subdir.mk
-include Libraries/iLLD/TC27D/Tricore/Cpu/Irq/subdir.mk
-include Libraries/iLLD/TC27D/Tricore/Cpu/CStart/subdir.mk
-include Libraries/iLLD/TC27D/Tricore/Asclin/Std/subdir.mk
-include Libraries/iLLD/TC27D/Tricore/Asclin/Asc/subdir.mk
-include Libraries/Service/CpuGeneric/StdIf/subdir.mk
-include Libraries/Infra/Platform/Tricore/Compilers/subdir.mk
-include GPIO/subdir.mk
-include Encoder/subdir.mk
-include Configurations/Debug/subdir.mk
-include ADC/subdir.mk
-include subdir.mk
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := 06_PWM_GTM
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
06_PWM_GTM.hex \

SECONDARY_LIST += \
06_PWM_GTM.lst \

SECONDARY_SIZE += \
06_PWM_GTM.siz \


# All Target
all: main-build

# Main-build Target
main-build: 06_PWM_GTM.elf secondary-outputs

# Tool invocations
06_PWM_GTM.elf: $(OBJS) ../Lcf_Gnuc_Tricore_Tc.lsl makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: AURIX GCC Linker'
	tricore-elf-gcc -nocrt0 -T"../Lcf_Gnuc_Tricore_Tc.lsl" -Wl,--gc-sections -mtc161 -o "06_PWM_GTM.elf" $(OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

06_PWM_GTM.hex: 06_PWM_GTM.elf makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Invoking: AURIX Object Copy'
	tricore-elf-objcopy -O ihex "06_PWM_GTM.elf" "06_PWM_GTM.hex"
	@echo 'Finished building: $@'
	@echo ' '

06_PWM_GTM.lst: 06_PWM_GTM.elf makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Invoking: AURIX Create Listing'
	tricore-elf-objdump -h -S "06_PWM_GTM.elf" > "06_PWM_GTM.lst"
	@echo 'Finished building: $@'
	@echo ' '

06_PWM_GTM.siz: 06_PWM_GTM.elf makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Invoking: AURIX Print Size'
	tricore-elf-size  --format=berkeley "06_PWM_GTM.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) 06_PWM_GTM.elf 06_PWM_GTM.hex 06_PWM_GTM.lst 06_PWM_GTM.siz
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents main-build

-include ../makefile.targets
