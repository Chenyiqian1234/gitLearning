################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"$(SOURCE)/libai.c" \
"$(SOURCE)/libcan.c" \
"$(SOURCE)/libdi.c" \
"$(SOURCE)/libdo.c" \
"$(SOURCE)/libdataflash.c" \
"$(SOURCE)/libevent.c" \
"$(SOURCE)/libmain.c" \
"$(SOURCE)/libmotor.c" \
"$(SOURCE)/libpi.c" \
"$(SOURCE)/libpwm.c" \
"$(SOURCE)/libpublic.c" \
"$(SOURCE)/libsci.c" \
"$(SOURCE)/libspi0.c" \
"$(SOURCE)/libspi1.c" \
"$(SOURCE)/libsystem.c" \
"$(SOURCE)/libtimer.c" \
"$(SOURCE)/libtimerb0.c" \
"$(SOURCE)/libtimerb1.c" \
"$(SOURCE)/libtimerb2.c" \
"$(SOURCE)/libvardefine.c" \
"$(SOURCE)/libwatchdog.c" \

C_SRCS += \
$(SOURCE)/libai.c \
$(SOURCE)/libcan.c \
$(SOURCE)/libdi.c \
$(SOURCE)/libdo.c \
$(SOURCE)/libdataflash.c \
$(SOURCE)/libevent.c \
$(SOURCE)/libmain.c \
$(SOURCE)/libmotor.c \
$(SOURCE)/libpi.c \
$(SOURCE)/libpwm.c \
$(SOURCE)/libpublic.c \
$(SOURCE)/libsci.c \
$(SOURCE)/libspi0.c \
$(SOURCE)/libspi1.c \
$(SOURCE)/libsystem.c \
$(SOURCE)/libtimer.c \
$(SOURCE)/libtimerb0.c \
$(SOURCE)/libtimerb1.c \
$(SOURCE)/libtimerb2.c \
$(SOURCE)/libvardefine.c \
$(SOURCE)/libwatchdog.c \

OBJS += \
./Source/libai_c.obj \
./Source/libcan_c.obj \
./Source/libdi_c.obj \
./Source/libdo_c.obj \
./Source/libdataflash_c.obj \
./Source/libevent_c.obj \
./Source/libmain_c.obj \
./Source/libmotor_c.obj \
./Source/libpi_c.obj \
./Source/libpwm_c.obj \
./Source/libpublic_c.obj \
./Source/libsci_c.obj \
./Source/libspi0_c.obj \
./Source/libspi1_c.obj \
./Source/libsystem_c.obj \
./Source/libtimer_c.obj \
./Source/libtimerb0_c.obj \
./Source/libtimerb1_c.obj \
./Source/libtimerb2_c.obj \
./Source/libvardefine_c.obj \
./Source/libwatchdog_c.obj \

OBJS_QUOTED += \
"./Source/libai_c.obj" \
"./Source/libcan_c.obj" \
"./Source/libdi_c.obj" \
"./Source/libdo_c.obj" \
"./Source/libdataflash_c.obj" \
"./Source/libevent_c.obj" \
"./Source/libmain_c.obj" \
"./Source/libmotor_c.obj" \
"./Source/libpi_c.obj" \
"./Source/libpwm_c.obj" \
"./Source/libpublic_c.obj" \
"./Source/libsci_c.obj" \
"./Source/libspi0_c.obj" \
"./Source/libspi1_c.obj" \
"./Source/libsystem_c.obj" \
"./Source/libtimer_c.obj" \
"./Source/libtimerb0_c.obj" \
"./Source/libtimerb1_c.obj" \
"./Source/libtimerb2_c.obj" \
"./Source/libvardefine_c.obj" \
"./Source/libwatchdog_c.obj" \

C_DEPS += \
./Source/LibAI_c.d \
./Source/LibCAN_c.d \
./Source/LibDI_c.d \
./Source/LibDO_c.d \
./Source/LibDataFlash_c.d \
./Source/LibEvent_c.d \
./Source/LibMain_c.d \
./Source/LibMotor_c.d \
./Source/LibPI_c.d \
./Source/LibPWM_c.d \
./Source/LibPublic_c.d \
./Source/LibSCI_c.d \
./Source/LibSPI0_c.d \
./Source/LibSPI1_c.d \
./Source/LibSystem_c.d \
./Source/LibTimer_c.d \
./Source/LibTimerB0_c.d \
./Source/LibTimerB1_c.d \
./Source/LibTimerB2_c.d \
./Source/LibVarDefine_c.d \
./Source/LibWatchDog_c.d \

C_DEPS_QUOTED += \
"./Source/LibAI_c.d" \
"./Source/LibCAN_c.d" \
"./Source/LibDI_c.d" \
"./Source/LibDO_c.d" \
"./Source/LibDataFlash_c.d" \
"./Source/LibEvent_c.d" \
"./Source/LibMain_c.d" \
"./Source/LibMotor_c.d" \
"./Source/LibPI_c.d" \
"./Source/LibPWM_c.d" \
"./Source/LibPublic_c.d" \
"./Source/LibSCI_c.d" \
"./Source/LibSPI0_c.d" \
"./Source/LibSPI1_c.d" \
"./Source/LibSystem_c.d" \
"./Source/LibTimer_c.d" \
"./Source/LibTimerB0_c.d" \
"./Source/LibTimerB1_c.d" \
"./Source/LibTimerB2_c.d" \
"./Source/LibVarDefine_c.d" \
"./Source/LibWatchDog_c.d" \

OBJS_OS_FORMAT += \
./Source/libai_c.obj \
./Source/libcan_c.obj \
./Source/libdi_c.obj \
./Source/libdo_c.obj \
./Source/libdataflash_c.obj \
./Source/libevent_c.obj \
./Source/libmain_c.obj \
./Source/libmotor_c.obj \
./Source/libpi_c.obj \
./Source/libpwm_c.obj \
./Source/libpublic_c.obj \
./Source/libsci_c.obj \
./Source/libspi0_c.obj \
./Source/libspi1_c.obj \
./Source/libsystem_c.obj \
./Source/libtimer_c.obj \
./Source/libtimerb0_c.obj \
./Source/libtimerb1_c.obj \
./Source/libtimerb2_c.obj \
./Source/libvardefine_c.obj \
./Source/libwatchdog_c.obj \


# Each subdirectory must supply rules for building sources it contributes
Source/libai_c.obj: $(SOURCE)/libai.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: DSC Compiler'
	"$(DSC_ToolsDirEnv)/mwcc56800e" -c @@"Source/LibAI.args" -o "Source/libai_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Source/LibAI_c.d: $(SOURCE)/libai.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Source/libcan_c.obj: $(SOURCE)/libcan.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: DSC Compiler'
	"$(DSC_ToolsDirEnv)/mwcc56800e" -c @@"Source/LibCAN.args" -o "Source/libcan_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Source/LibCAN_c.d: $(SOURCE)/libcan.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Source/libdi_c.obj: $(SOURCE)/libdi.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: DSC Compiler'
	"$(DSC_ToolsDirEnv)/mwcc56800e" -c @@"Source/LibDI.args" -o "Source/libdi_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Source/LibDI_c.d: $(SOURCE)/libdi.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Source/libdo_c.obj: $(SOURCE)/libdo.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: DSC Compiler'
	"$(DSC_ToolsDirEnv)/mwcc56800e" -c @@"Source/LibDO.args" -o "Source/libdo_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Source/LibDO_c.d: $(SOURCE)/libdo.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Source/libdataflash_c.obj: $(SOURCE)/libdataflash.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: DSC Compiler'
	"$(DSC_ToolsDirEnv)/mwcc56800e" -c @@"Source/LibDataFlash.args" -o "Source/libdataflash_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Source/LibDataFlash_c.d: $(SOURCE)/libdataflash.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Source/libevent_c.obj: $(SOURCE)/libevent.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: DSC Compiler'
	"$(DSC_ToolsDirEnv)/mwcc56800e" -c @@"Source/LibEvent.args" -o "Source/libevent_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Source/LibEvent_c.d: $(SOURCE)/libevent.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Source/libmain_c.obj: $(SOURCE)/libmain.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: DSC Compiler'
	"$(DSC_ToolsDirEnv)/mwcc56800e" -c @@"Source/LibMain.args" -o "Source/libmain_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Source/LibMain_c.d: $(SOURCE)/libmain.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Source/libmotor_c.obj: $(SOURCE)/libmotor.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: DSC Compiler'
	"$(DSC_ToolsDirEnv)/mwcc56800e" -c @@"Source/LibMotor.args" -o "Source/libmotor_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Source/LibMotor_c.d: $(SOURCE)/libmotor.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Source/libpi_c.obj: $(SOURCE)/libpi.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: DSC Compiler'
	"$(DSC_ToolsDirEnv)/mwcc56800e" -c @@"Source/LibPI.args" -o "Source/libpi_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Source/LibPI_c.d: $(SOURCE)/libpi.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Source/libpwm_c.obj: $(SOURCE)/libpwm.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: DSC Compiler'
	"$(DSC_ToolsDirEnv)/mwcc56800e" -c @@"Source/LibPWM.args" -o "Source/libpwm_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Source/LibPWM_c.d: $(SOURCE)/libpwm.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Source/libpublic_c.obj: $(SOURCE)/libpublic.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: DSC Compiler'
	"$(DSC_ToolsDirEnv)/mwcc56800e" -c @@"Source/LibPublic.args" -o "Source/libpublic_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Source/LibPublic_c.d: $(SOURCE)/libpublic.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Source/libsci_c.obj: $(SOURCE)/libsci.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: DSC Compiler'
	"$(DSC_ToolsDirEnv)/mwcc56800e" -c @@"Source/LibSCI.args" -o "Source/libsci_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Source/LibSCI_c.d: $(SOURCE)/libsci.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Source/libspi0_c.obj: $(SOURCE)/libspi0.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: DSC Compiler'
	"$(DSC_ToolsDirEnv)/mwcc56800e" -c @@"Source/LibSPI0.args" -o "Source/libspi0_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Source/LibSPI0_c.d: $(SOURCE)/libspi0.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Source/libspi1_c.obj: $(SOURCE)/libspi1.c
	@echo 'Building file: $<'
	@echo 'Executing target #14 $<'
	@echo 'Invoking: DSC Compiler'
	"$(DSC_ToolsDirEnv)/mwcc56800e" -c @@"Source/LibSPI1.args" -o "Source/libspi1_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Source/LibSPI1_c.d: $(SOURCE)/libspi1.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Source/libsystem_c.obj: $(SOURCE)/libsystem.c
	@echo 'Building file: $<'
	@echo 'Executing target #15 $<'
	@echo 'Invoking: DSC Compiler'
	"$(DSC_ToolsDirEnv)/mwcc56800e" -c @@"Source/LibSystem.args" -o "Source/libsystem_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Source/LibSystem_c.d: $(SOURCE)/libsystem.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Source/libtimer_c.obj: $(SOURCE)/libtimer.c
	@echo 'Building file: $<'
	@echo 'Executing target #16 $<'
	@echo 'Invoking: DSC Compiler'
	"$(DSC_ToolsDirEnv)/mwcc56800e" -c @@"Source/LibTimer.args" -o "Source/libtimer_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Source/LibTimer_c.d: $(SOURCE)/libtimer.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Source/libtimerb0_c.obj: $(SOURCE)/libtimerb0.c
	@echo 'Building file: $<'
	@echo 'Executing target #17 $<'
	@echo 'Invoking: DSC Compiler'
	"$(DSC_ToolsDirEnv)/mwcc56800e" -c @@"Source/LibTimerB0.args" -o "Source/libtimerb0_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Source/LibTimerB0_c.d: $(SOURCE)/libtimerb0.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Source/libtimerb1_c.obj: $(SOURCE)/libtimerb1.c
	@echo 'Building file: $<'
	@echo 'Executing target #18 $<'
	@echo 'Invoking: DSC Compiler'
	"$(DSC_ToolsDirEnv)/mwcc56800e" -c @@"Source/LibTimerB1.args" -o "Source/libtimerb1_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Source/LibTimerB1_c.d: $(SOURCE)/libtimerb1.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Source/libtimerb2_c.obj: $(SOURCE)/libtimerb2.c
	@echo 'Building file: $<'
	@echo 'Executing target #19 $<'
	@echo 'Invoking: DSC Compiler'
	"$(DSC_ToolsDirEnv)/mwcc56800e" -c @@"Source/LibTimerB2.args" -o "Source/libtimerb2_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Source/LibTimerB2_c.d: $(SOURCE)/libtimerb2.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Source/libvardefine_c.obj: $(SOURCE)/libvardefine.c
	@echo 'Building file: $<'
	@echo 'Executing target #20 $<'
	@echo 'Invoking: DSC Compiler'
	"$(DSC_ToolsDirEnv)/mwcc56800e" -c @@"Source/LibVarDefine.args" -o "Source/libvardefine_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Source/LibVarDefine_c.d: $(SOURCE)/libvardefine.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Source/libwatchdog_c.obj: $(SOURCE)/libwatchdog.c
	@echo 'Building file: $<'
	@echo 'Executing target #21 $<'
	@echo 'Invoking: DSC Compiler'
	"$(DSC_ToolsDirEnv)/mwcc56800e" -c @@"Source/LibWatchDog.args" -o "Source/libwatchdog_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Source/LibWatchDog_c.d: $(SOURCE)/libwatchdog.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


