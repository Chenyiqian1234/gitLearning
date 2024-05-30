################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
ASM_SRCS += \
$(GITLEARNING)/324/support/mc56f836x_vector.asm \

ASM_SRCS_QUOTED += \
"$(GITLEARNING)/324/support/mc56f836x_vector.asm" \

OBJS += \
./MC56F8367\ support/interrupt\ vectors/mc56f836x_vector_asm.obj \

ASM_DEPS += \
./MC56F8367\ support/interrupt\ vectors/MC56F836x_vector_asm.d \

OBJS_QUOTED += \
"./MC56F8367 support/interrupt vectors/mc56f836x_vector_asm.obj" \

ASM_DEPS_QUOTED += \
"./MC56F8367 support/interrupt vectors/MC56F836x_vector_asm.d" \

OBJS_OS_FORMAT += \
./MC56F8367\ support/interrupt\ vectors/mc56f836x_vector_asm.obj \


# Each subdirectory must supply rules for building sources it contributes
MC56F8367\ support/interrupt\ vectors/mc56f836x_vector_asm.obj: $(GITLEARNING)/324/support/mc56f836x_vector.asm
	@echo 'Building file: $<'
	@echo 'Executing target #25 $<'
	@echo 'Invoking: DSC Assembler'
	"$(DSC_ToolsDirEnv)/mwasm56800e" @@"MC56F8367 support/interrupt vectors/MC56F836x_vector.args" -o "MC56F8367 support/interrupt vectors/mc56f836x_vector_asm.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

MC56F8367\ support/interrupt\ vectors/MC56F836x_vector_asm.d: $(GITLEARNING)/324/support/mc56f836x_vector.asm
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


