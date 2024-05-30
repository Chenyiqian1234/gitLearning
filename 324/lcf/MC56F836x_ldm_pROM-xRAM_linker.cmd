



# ----------------------------------------------------

# Metrowerks sample code

# linker command file for DSP56836x EVM
# using 
#    flash pROM
#    flash xROM 
#    internal xRAM 
#    Small Data Model (SDM)

# ----------------------------------------------------



# see end of file for additional notes & revision history
# see Motorola docs for specific EVM memory map



# memory use for this LCF: 
# interrupt vectors --> flash pROM starting at zero
#      program code --> flash pROM
#         constants --> flash xROM 
#      dynamic data --> flash pROM (copied to xRAM with init) 



# CodeWarrior preference settings:
#
#   M56800E Processor:
#     Small Program Model: OFF
#        Large Data Model: ON
#
#   M56800E Assembler:
#        Default Data Memory Model: 24-bit
#     Default Program Memory Model: 19-bit
#
#
#   M56800E Target pref panel:
#     config file: 56836x_flash.cfg
#     (sets OMR for internal memory)


# EVM board jumpers:
#     JG4 on
#     (if not set by config file)




# 56836x memory map for:
#    Small Data Model (SDM)
#    x memory: EX=0 (OMR)
#    p memory: mode 0
 
 
# x memory above 7FFF not available with SDM
# complete 56835 x-RAM shown for clarity
# see below for memory notes


MEMORY 
{
    .p_interrupts_ROM     (RX)  : ORIGIN = 0x0000,   LENGTH = 0x00AC   # reserved for interrupts
    .p_flash_ROM          (RX)  : ORIGIN = 0x00AC,   LENGTH = 0x3FF54  # 256K words contiguous flash minus interrupt space

     # p_flash_ROM_data mirrors internal xRAM, mapping to origin and length
     # the "X" flag in "RX" tells the debugger to download to p-memory.
     # the download to p-memory is directed to the address determined by AT
     # in the section definition below.  
     
    .p_flash_ROM_data     (RX)  : ORIGIN = 0x0001,   LENGTH = 0x3FFF   # internal xRAM mirror

    .p_boot_flash_ROM     (RX)  : ORIGIN = 0x40000,  LENGTH = 0x4000   # 16K words  
#   .p_reserved                 : ORIGIN = 0x44000,  LENGTH = 0xB800   # 46K words
    .p_internal_RAM       (RWX) : ORIGIN = 0x4F800,  LENGTH = 0x0800   # 2K words
    .p_external_RAM       (RWX) : ORIGIN = 0x50000,  LENGTH = 0x0000   # max available   
    .x_internal_RAM       (RW)  : ORIGIN = 0x0001,   LENGTH = 0x3FFF  
    .x_const_flash_ROM    (RW)  : ORIGIN = 0x4000,   LENGTH = 0x0800   # 2K  words
    .x_flash_ROM          (RW)  : ORIGIN = 0x4800,   LENGTH = 0x3800   # 14K words
    .x_external_RAM       (RW)  : ORIGIN = 0x8000,   LENGTH = 0x7000   
    .x_onchip_peripherals (RW)  : ORIGIN = 0xF000,   LENGTH = 0x1000   
    .x_external_RAM_2     (RW)  : ORIGIN = 0x10000,  LENGTH = 0xFEFF00 
    .x_EOnCE              (RW)  : ORIGIN = 0xFFFF00, LENGTH = 0x0000   
}






# we ensure the interrupt vector section is not deadstripped here
# the label "interrupt_vectors" comes from file 56835x_vector.asm

KEEP_SECTION{ interrupt_vectors.text}





SECTIONS 
{
    .interrupt_code :
    {
        * (interrupt_vectors.text)
       
    } > .p_interrupts_ROM
   
   
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
				
		# save address where for the data start in pROM
		 
        . = ALIGN(2);
 	    __pROM_data_start = .;  
 	    
	} > .p_flash_ROM

     
     
    .data_in_xROM : 
	{                                        	
        # constant data is placed in x flash ROM
        * (.const.data.char)   # used if "Emit Separate Char Data Section" enabled
        * (.const.data) 
        
	} > .x_const_flash_ROM	 

    



# AT sets the download address
# the download stashes the data just after the program code
# as determined by our saved pROM data start variable

	.data_in_p_flash_ROM : AT(__pROM_data_start) 
	{                             
	    # the data sections flashed to pROM
	    # save data start so we can copy data later to xRAM
	    
 	    __xRAM_data_start = .; 
 	    
 	    
        * (.data.char)  # used if "Emit Separate Char Data Section"    
        * (.data)	    
	    * (fp_state.data)
		* (rtlib.data)
 	    
 	    
 	    # save data end and calculate data block size
 	    
 	    . = ALIGN(2);       # ensure _data_size is word-aligned
 	                        # since rom-to-ram copy is by word
 	                        # and we could have odd-number bytes
 	                        # in .data section since 56800E 
 	                        # has byte addressing


		__xRAM_data_end = .;
		__data_size = __xRAM_data_end - __xRAM_data_start;

	} > .p_flash_ROM_data	 # this section is designated as p-memory 
	                         # with X flag in the memory map
	                         # the start address and length map to 
	                         # actual internal xRAM
	
	
		
		
		
	.data : 
	{                             

        # save space for the pROM data copy 
        
        . = __data_size +1 ;

		        
        # .bss sections
        
        . = ALIGN(2);
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
        __heap_size = 0x200;
        __heap_end  = __heap_addr + __heap_size; 
        . = __heap_end;



        # setup the stack address 
        
        _min_stack_size = 0x400;
        _stack_addr = __heap_end + 2;
        _stack_end  = _stack_addr + _min_stack_size;
        . = _stack_end;
        
        
        
        # used by MSL 
            
        F_heap_addr   = __heap_addr;
        F_heap_end    = __heap_end;
        
     
        
	# stationery init code uses these globals:

        F_Lstack_addr   = _stack_addr;
        
        # rom-to-ram utility
		F_Ldata_size     = __data_size;
		F_Ldata_RAM_addr = __xRAM_data_start;
		F_Ldata_ROM_addr = __pROM_data_start;
		
        F_xROM_to_xRAM   = 0x0000;
        F_pROM_to_xRAM   = 0x0001; 	# true
               
	 	# zeroBSS utility
        F_Lbss_addr   = __bss_addr;
        F_Lbss_size   = __bss_size;
	
	} > .x_internal_RAM	 	                    	
}



# -------------------------------------------------------
# additional notes:


# about the reserved sections:

# p_interrupts_RAM -- reserved in internal pRAM
# memory space reserved for interrupt vectors
# interrupt vectors must start at address zero




# about the memory map:

# SMM xRAM limit is 0x7FFF





# about LCF conventions:

# program memory (p memory)
# (RWX) read/write/execute for pRAM
# (RX) read/execute for flashed pROM

# data memory (X memory)
# (RW) read/write for xRAM
# (R)  read for data flashed xROM or reserved x memory

# LENGTH = next start address - previous
# LENGTH = 0x0000 means use all remaing memory




# about ROM-to-RAM copying at init time:

# In embedded programming, it is common for a portion of 
# a program resident in ROM to be copied into RAM at runtime.
# For starters, program variables cannot be accessed until 
# they are copied to RAM. 

# To indicate data or code that is meant to be copied 
# from ROM to RAM,the data or code is given two addresses.

# One address is the resident location in ROM (defined by 
# the linker command file). The other is the intended
# location in RAM (defined in C code where we will 
# do the actual copying).

# To create a section with the resident location in ROM 
# and an intended location in RAM, you define the two addresses 
# in the linker command file.

# Use the MEMORY segment to specify the intended RAM location,
# and the AT(address)parameter to specify the resident ROM address.


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
# 040723 R7.0  a.h. 56836x


# -- end -- 
