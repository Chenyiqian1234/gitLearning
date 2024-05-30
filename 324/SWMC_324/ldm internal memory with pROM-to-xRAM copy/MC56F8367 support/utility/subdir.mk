################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
ASM_SRCS += \
$(GITLEARNING)/324/support/dsp56800e_promxram.asm \
$(GITLEARNING)/324/support/dsp56800e_zerobss.asm \

ASM_SRCS_QUOTED += \
"$(GITLEARNING)/324/support/dsp56800e_promxram.asm" \
"$(GITLEARNING)/324/support/dsp56800e_zerobss.asm" \

OBJS += \
./MC56F8367\ support/utility/dsp56800e_promxram_asm.obj \
./MC56F8367\ support/utility/dsp56800e_zerobss_asm.obj \

ASM_DEPS += \
./MC56F8367\ support/utility/DSP56800E_promxram_asm.d \
./MC56F8367\ support/utility/DSP56800E_zeroBSS_asm.d \

OBJS_QUOTED += \
"./MC56F8367 support/utility/dsp56800e_promxram_asm.obj" \
"./MC56F8367 support/utility/dsp56800e_zerobss_asm.obj" \

ASM_DEPS_QUOTED += \
"./MC56F8367 support/utility/DSP56800E_promxram_asm.d" \
"./MC56F8367 support/utility/DSP56800E_zeroBSS_asm.d" \

OBJS_OS_FORMAT += \
./MC56F8367\ support/utility/dsp56800e_promxram_asm.obj \
./MC56F8367\ support/utility/dsp56800e_zerobss_asm.obj \


# Each subdirectory must supply rules for building sources it contributes
MC56F8367\ support/utility/dsp56800e_promxram_asm.obj: $(GITLEARNING)/324/support/dsp56800e_promxram.asm
	@echo 'Building file: $<'
	@echo 'Executing target #22 $<'
	@echo 'Invoking: DSC Assembler'
	"$(DSC_ToolsDirEnv)/mwasm56800e" @@"MC56F8367 support/utility/DSP56800E_promxram.args" -o "MC56F8367 support/utility/dsp56800e_promxram_asm.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

MC56F8367\ support/utility/DSP56800E_promxram_asm.d: $(GITLEARNING)/324/support/dsp56800e_promxram.asm
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

MC56F8367\ support/utility/dsp56800e_zerobss_asm.obj: $(GITLEARNING)/324/support/dsp56800e_zerobss.asm
	@echo 'Building file: $<'
	@echo 'Executing target #23 $<'
	@echo 'Invoking: DSC Assembler'
	"$(DSC_ToolsDirEnv)/mwasm56800e" @@"MC56F8367 support/utility/DSP56800E_zeroBSS.args" -o "MC56F8367 support/utility/dsp56800e_zerobss_asm.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

MC56F8367\ support/utility/DSP56800E_zeroBSS_asm.d: $(GITLEARNING)/324/support/dsp56800e_zerobss.asm
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


