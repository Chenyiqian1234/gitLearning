################################################################################
# Automatically-generated file. Do not edit!
################################################################################

#Progress monitor hint: 47
first : all
-include ../makefile.init

# This file contains definitions of environment variables used in the makefiles and .args files if exist.
-include makefile.local

RM := "$(GNU_Make_Install_DirEnv)/rm" -f

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include Source/subdir.mk
-include MC56F8367\ support/utility/subdir.mk
-include MC56F8367\ support/startup/subdir.mk
-include MC56F8367\ support/interrupt\ vectors/subdir.mk
-include Application/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
ldm_pROM-xRAM.elf \

EXECUTABLES_QUOTED += \
"ldm_pROM-xRAM.elf" \

EXECUTABLES_OS_FORMAT += \
ldm_pROM-xRAM.elf \


# All Target
all: warning-messages explicit-dependencies ldm_pROM-xRAM.elf

# Tool invocations
ldm_pROM-xRAM.elf: $(OBJS) $(USER_OBJS) $(GITLEARNING)/324/lcf/MC56F836x_ldm_pROM-xRAM_linker.cmd
	@echo 'Building target: $@'
	@echo 'Executing target #48 $@'
	@echo 'Invoking: DSC Linker'
	"$(DSC_ToolsDirEnv)/mwld56800e" -o "ldm_pROM-xRAM.elf" @@"ldm_pROM-xRAM.args"  $(USER_OBJS_QUOTED)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(S_DEPS_QUOTED) $(CPP_DEPS_QUOTED) $(CC_DEPS_QUOTED) "./*/*.obj" "./*/*/*.obj"  $(S_UPPER_DEPS_QUOTED) $(CXX_DEPS_QUOTED) "./*/*/*.d"  $(ASM_UPPER_DEPS_QUOTED) $(C_UPPER_DEPS_QUOTED) $(C++_DEPS_QUOTED) $(EXECUTABLES_QUOTED) "./*/*.d"  $(ProjDirPath)/ldm internal memory with pROM-to-xRAM copy/ldm_pROM-xRAM.elf
	-@echo ' '

.PHONY: all clean dependents explicit-dependencies warning-messages
.SECONDARY:

-include ../makefile.targets

explicit-dependencies: $(GITLEARNING)/324/lcf/MC56F836x_ldm_pROM-xRAM_linker.cmd 

warning-messages: 

