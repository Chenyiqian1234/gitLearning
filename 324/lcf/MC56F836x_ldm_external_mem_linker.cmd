


# ----------------------------------------------------

# Metrowerks sample code

# linker command file for DSP56836x EVM
# using 
#    external pRAM MA=1
#    external xRAM EX=0
#    Large Data Model (LDM)


# ----------------------------------------------------

    
# see end of file for additional notes & revision history
# see Motorola docs for specific EVM memory map


# memory use for this LCF: 
# interrupt vectors --> external pRAM starting at zero
#      program code --> external pRAM
#         constants --> external xRAM
#      dynamic data --> external xRAM 




# CodeWarrior preference settings:
#
#   M56800E Processor:
#     Small Program Model: OFF
#        Large Data Model: ON
#
#
#   M56800E Assembler:
#        Default Data Memory Model: 24-bit
#     Default Program Memory Model: 19-bit
#
#   M56800E Target:
#      config file: 56836x_ext_xp.cfg
#      (sets OMR for external memory)


#  EVM board jumpers:
#      JG4 off
#     (if not set by config file)




# 56836x memory map for:
#    Large Data Model (LDM)
#    x memory: OMR EX=0
#    p memory: OMR MA=1 (mode=1, EMI_MODE=1)
 



MEMORY 
{
    .p_interrupts_ext_RAM (RWX) : ORIGIN = 0x0000,   LENGTH = 0x00AC   # reserved for interrupts
    .p_external_RAM       (RWX) : ORIGIN = 0x00AC,   LENGTH = 0x0000   # the max available 
    .x_internal_RAM       (RW)  : ORIGIN = 0x0001,   LENGTH = 0x3FFF  
    .x_flash_ROM          (RW)  : ORIGIN = 0x4000,   LENGTH = 0x4000  
    .x_external_RAM       (RW)  : ORIGIN = 0x8000,   LENGTH = 0x7000   
    .x_onchip_peripherals (RW)  : ORIGIN = 0xF000,   LENGTH = 0x1000   
    .x_external_RAM_2     (RW)  : ORIGIN = 0x10000,  LENGTH = 0xFEFF00 
    .x_EOnCE              (RW)  : ORIGIN = 0xFFFF00, LENGTH = 0x0000   
}










# we ensure the interrupt vector section is not deadstripped here
# the label "interrupt_vectors" comes from file 56835x_vector.asm

KEEP_SECTION{ interrupt_vectors.text }



SECTIONS 
{
    .interrupt_vectors :
    {
        * (interrupt_vectors.text)  
       
    } > .p_interrupts_ext_RAM
    
    
    
    .executing_code :
    {
        # .text sections
        
 		* (startup.text)
        * (utility.text)
		* (interrupt_routines.text)
        * (rtlib.text)
        * (fp_engine.text)
        * (.text)
        * (user.text)    
        
    } > .p_external_RAM





    .data :
    {    
        # .data sections
        
        * (.const.data.char)   # used if "Emit Separate Char Data Section" enabled
        * (.const.data)
        * (fp_state.data)
        * (rtlib.data)
        * (.data.char)         # used if "Emit Separate Char Data Section" enabled
        * (.data)
        
        
        
        # .bss sections
        
        * (rtlib.bss.lo)
        * (rtlib.bss)
        . = ALIGN(2);
        __bss_addr = .;
        * (.bss.char)         # used if "Emit Separate Char Data Section" enabled
        * (.bss)
        __bss_end   = .;

		__bss_size = __bss_end - __bss_addr;



        # setup the heap address 
        
        . = ALIGN(4);
        __heap_addr = .;
        __heap_size = 0x100;
        __heap_end  = __heap_addr + __heap_size; 
        . = __heap_end;



        # setup the stack address 
        
        _min_stack_size = 0x200;
        _stack_addr = __heap_end + 2;
        _stack_end  = _stack_addr + _min_stack_size;
        . = _stack_end;
        
        
        
        # used by MSL 
            
        F_heap_addr   = __heap_addr;
        F_heap_end    = __heap_end;
        
     
        
	# stationery init code uses these globals:

        F_Lstack_addr   = _stack_addr;
        
        
		# next not used in this LCF 
		# we define anyway so init code will link 
		# these can be removed with removal of rom-to-ram
		# copy code in init file
	
		F_Ldata_size     = 0x0000;
		F_Ldata_RAM_addr = 0x0000;
		F_Ldata_ROM_addr = 0x0000;		
        F_xROM_to_xRAM   = 0x0000; 
        F_pROM_to_xRAM   = 0x0000; 
        
               
	 	# zeroBSS utility
        F_Lbss_addr   = __bss_addr;
        F_Lbss_size   = __bss_size;
			
    } > .x_external_RAM    
}





# -------------------------------------------------------
# additional notes:


# about the reserved sections:

# p_interrupts_RAM -- reserved in internal pRAM
# memory space reserved for interrupt vectors
# interrupt vectors must start at address zero
# interrupt vector space size is 0xA2




# about the memory map:

# SDM xRAM limit is 0x7FFF





# about LCF conventions:

# program memory (p memory)
# (RWX) read/write/execute for pRAM
# (RX) read/execute for flashed pROM

# data memory (X memory)
# (RW) read/write for xRAM
# (R)  read for data flashed xROM or reserved x memory

# LENGTH = next start address - previous
# LENGTH = 0x0000 means use all remaing memory







# revision history 

# 011226 R1.0  c.m. first version
# 020220 R1.1  a.h. updates
# 020308 R1.1  a.h. 56838E
# 021101 R2.0  a.h. R2.0 prep
# 021204 R2.01 a.h. bss align by 1
# 030222 R2.1  a.h. 568345/346
# 030630 R6.0  a.h. ldm pROM-xRAM
# 030814 R6.0  a.h. align(1) for data
# 030916 R6.01 a.h. 56835x
# 040723 R7.0  a.h. 56836x



# end
