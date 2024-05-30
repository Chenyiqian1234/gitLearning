

 

; metrowerks sample code



;	interrupt vectors for MC56F836x
;   based on "Monza/Dakar/Hockenheim_SS_Version_3_6"  3/11/2004  2:22pm

;   notes from Motorola documentation 

;   1. Two words are allocated for each entry in the vector table. 
;      This does not allow the full address range to be
;      referenced from the vector table; providing only 19 bits of address.
;   2. If the VBA is set to 0200 (VBA=0000 for Mode 1, EMI_MODE=0) 
;       the first two locations of the vector table are the chip reset addresses; 
;       therefore, these locations are not interrupt vectors.




	section interrupt_routines
	org	p:
	
MC56F836x_intRoutine:
	debughlt
	nop
	nop
	rti


; illegal instruction interrupt ($04)

MC56F836x_illegal:
	debughlt	
	nop
	nop
	rti


; hardware stack overflow interrupt ($08)
	
MC56F836x_HWSOverflow:
	debughlt	
	nop
	nop
	rti
	
	
; misaligned long word access interrupt ($0A)
	
MC56F836x_misalign:
	debughlt	                     
	nop
	nop
	rti


 ; PLL lost of lock interrupt ($28)
 
MC56F836x_PLL:
	debughlt	                    
	nop
	nop 
	rti
    endsec
    
    
	section interrupt_vectors
	org	p:
	
	global	MC56F836x_intVec

MC56F836x_intVec:

	jsr >Finit_MC56F83xx_        ; RESET  (see note #2 above)                      ($00)
	jsr >MC56F836x_intRoutine    ; COP Watchdog reset (see note #2 above)          ($02)
	jsr >MC56F836x_illegal       ; illegal instruction                             ($04)
	jsr >MC56F836x_intRoutine    ; software interrupt 3                            ($06)
	jsr >MC56F836x_HWSOverflow   ; hardware stack overflow                         ($08)
	jsr >MC56F836x_misalign      ; misaligned long word access                     ($0A)
	jsr >MC56F836x_intRoutine    ; EOnCE step counter                              ($0C)
	jsr >MC56F836x_intRoutine    ; EOnCE breakpoint unit 0                         ($0E)
	jsr >MC56F836x_intRoutine    ; reserved                                        ($10)
	jsr >MC56F836x_intRoutine    ; EOnCE trace buffer                              ($12)
	jsr >MC56F836x_intRoutine    ; EOnCE transmit register empty                   ($14)
	jsr >MC56F836x_intRoutine    ; EOnCE receive register full                     ($16)
	jsr >MC56F836x_intRoutine    ; reserved                                        ($18)
	jsr >MC56F836x_intRoutine    ; reserved                                        ($1A)
	jsr >MC56F836x_intRoutine    ; software interrupt 2                            ($1C)
	jsr >MC56F836x_intRoutine    ; software interrupt 1                            ($1E)
	jsr >MC56F836x_intRoutine    ; software interrupt 0                            ($20)
	jsr >FLibIrqaInterrupt       ; IRQA                                            ($22)
	jsr >FLibIrqbInterrupt       ; IRQB                                            ($24)
	jsr >MC56F836x_intRoutine    ; reserved                                        ($26)
	jsr >MC56F836x_PLL           ; Low Voltage Detector (power sense)              ($28)
	jsr >MC56F836x_intRoutine    ; PLL                                             ($2A)
	jsr >MC56F836x_intRoutine    ; HFM Error Interrupt                             ($2C)
	jsr >MC56F836x_intRoutine    ; HFM Command Complete                            ($2E)
	jsr >MC56F836x_intRoutine    ; HFM Command, data and address Buffers Empty     ($30)
	jsr >MC56F836x_intRoutine    ; reserved                                        ($32)
	jsr >MC56F836x_intRoutine    ; FlexCAN Bus Off                                 ($34)
	jsr >MC56F836x_intRoutine    ; FlexCAN Error                                   ($36)
	jsr >MC56F836x_intRoutine    ; FlexCAN Wake Up                                 ($38)
	jsr >FLibInterruptCan1Rec    ; FlexCAN Message Buffer Interrupt                ($3A)
	jsr >MC56F836x_intRoutine    ; GPIO F                                          ($3C)
	jsr >MC56F836x_intRoutine    ; GPIO E                                          ($3E)
	jsr >MC56F836x_intRoutine    ; GPIO D                                          ($40)
	jsr >MC56F836x_intRoutine    ; GPIO C                                          ($42)
	jsr >MC56F836x_intRoutine    ; GPIO B                                          ($44)
	jsr >MC56F836x_intRoutine    ; GPIO A                                          ($46)
	jsr >MC56F836x_intRoutine    ; reserved                                        ($48)
	jsr >MC56F836x_intRoutine    ; reserved                                        ($4A)
	jsr >FLibSpi1RecInterrupt    ; SPI 1 receiver full                             ($4C)
	jsr >MC56F836x_intRoutine    ; SPI 1 transmitter empty                         ($4E)
	jsr >MC56F836x_intRoutine    ; SPI 0 receiver full                             ($50)
	jsr >MC56F836x_intRoutine    ; SPI 0 transmitter empty                         ($52)
	jsr >MC56F836x_intRoutine    ; SCI 1 transmitter empty                         ($54)
	jsr >MC56F836x_intRoutine    ; SCI 1 transmitter idle                          ($56)
	jsr >MC56F836x_intRoutine    ; reserved                                        ($58)
	jsr >MC56F836x_intRoutine    ; SCI receiver error                              ($5A)
	jsr >MC56F836x_intRoutine    ; SCI receiver full                               ($5C)
	jsr >MC56F836x_intRoutine    ; quadrature decoder #1 home switch or watchdog   ($5E)
	jsr >MC56F836x_intRoutine    ; quadrature decoder #1 index pulse               ($60)
	jsr >MC56F836x_intRoutine    ; quadrature decoder #0 home switch or watchdog   ($62)
	jsr >MC56F836x_intRoutine    ; quadrature decoder #0 index pulse               ($64)
	jsr >MC56F836x_intRoutine    ; reserved                                        ($66)
	jsr >MC56F836x_intRoutine    ; timer D channel 0                               ($68)
	jsr >FLibInterruptTimerD1    ; timer D channel 1                               ($6a)
	jsr >FLibInterruptTimerD2    ; timer D channel 2                               ($6c)
	jsr >MC56F836x_intRoutine    ; timer D channel 3                               ($6e)
	jsr >MC56F836x_intRoutine    ; timer C channel 0                               ($70)
	jsr >MC56F836x_intRoutine    ; timer C channel 1                               ($72)
	jsr >MC56F836x_intRoutine    ; timer C channel 2                               ($74)
	jsr >MC56F836x_intRoutine    ; timer C channel 3                               ($76)
	jsr >FLibInterruptTimerB0    ; timer B channel 0                               ($78)
	jsr >FLibInterruptTimerB1    ; timer B channel 1                               ($7A)
	jsr >FLibInterruptTimerB2    ; timer B channel 2                               ($7C)
	jsr >MC56F836x_intRoutine    ; timer B channel 3                               ($7E)
	jsr >FLibInterruptTimerA0    ; timer A channel 0                               ($80)
	jsr >FLibInterruptTimerA1    ; timer A channel 1                               ($82)
	jsr >MC56F836x_intRoutine    ; timer A channel 2                               ($84)
	jsr >MC56F836x_intRoutine    ; timer A channel 3                               ($86)
	jsr >FLibInteruptSciEmpty    ; SC1 0 transmitter empty                         ($88)
	jsr >FLibInteruptSciIdle     ; SC1 0 transmitter idle                          ($8A)
	jsr >MC56F836x_intRoutine    ; reserved                                        ($8C)
	jsr >FLibInteruptSciRec      ; SC1 0 receiver error                            ($8E)
	jsr >FLibInteruptSciRec      ; SC1 0 receiver full                             ($90)
	jsr >FLibMcuAdcbInterrupt    ; ADC B conversion complete                       ($92)
	jsr >FLibMcuAdcaInterrupt    ; ADC A conversion complete                       ($94)
	jsr >MC56F836x_intRoutine    ; ADC B zero crossing of limit error              ($96)
	jsr >MC56F836x_intRoutine    ; ADC A zero crossing of limit error              ($98)
	jsr >MC56F836x_intRoutine    ; reload PWM B                                    ($9A)
	jsr >MC56F836x_intRoutine    ; reload PWM A                                    ($9C)
	jsr >MC56F836x_intRoutine    ; PWM B fault                                     ($9E)
	jsr >MC56F836x_intRoutine    ; PWM A fault                                     ($A0)
    jsr >MC56F836x_intRoutine    ; SW interrupt LP                                 ($A2)
    jsr >MC56F836x_intRoutine    ; FlexCAN Bus-Off                                 ($A4)
    jsr >MC56F836x_intRoutine    ; FlexCAN Error                                   ($A6)
    jsr >MC56F836x_intRoutine    ; FlexCAN Wake-up                                 ($A8)
    jsr >FLibInterruptCan0Rec    ; FlexCAN Message Buffer Interrupt                ($AA)
	endsec	

	end






