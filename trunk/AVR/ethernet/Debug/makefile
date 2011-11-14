################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include udpcom/win/subdir.mk
-include udpcom/unix/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
eth_rem_dev.lss \

SIZEDUMMY += \
sizedummy \


# All Target
all: eth_rem_dev.elf secondary-outputs

# Tool invocations
eth_rem_dev.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,eth_rem_dev.map -mmcu=atmega88 -o"eth_rem_dev.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

eth_rem_dev.lss: eth_rem_dev.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S eth_rem_dev.elf  >"eth_rem_dev.lss"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: eth_rem_dev.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega88 eth_rem_dev.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) eth_rem_dev.elf
	-@echo ' '

secondary-outputs: $(LSS) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
