; Multiboot header constants 
MBALIGN     equ 1 << 0              ; align loaded modules on page boundaries 
MEMINFO     equ 1 << 1              ; provide memory map 
FLAGS       equ MBALIGN | MEMINFO   ; Multiboot 'flag' field 
MAGIC       equ 0x1BADB002          ; 'magic number' lets bootloader find header 
CHECKSUM    equ -(MAGIC + FLAGS)    ; Checksum of above to prove we are multiboot 

; Declaring a multiboot header to mark program as a kernel 
section .multiboot
align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

; Create stack pointer register 
section .bss
align 16
stack_bottom:
resb 16384 ; 16 KiB
stack_top:

section .text
global _start:function (_start.end - _start)
_start:
    ; Kernel now has full absolute control of the CPU 

    ; Set ESP register to point to the top of the created stack (grows downward on x86) for C 
    mov esp, stack_top

    ; Initalize curcial processor state (TODO) 

    ; Enter high-level kernel (C) 
    extern kernel_main
    call kernel_main

    ; Infinite loop when computer has nothing to do
    ; 1) Disable interrupts with cli
    ; 2) Wait for next interrupt to arrive with hlt instruction (will lock up computer to it being disabled)
    ; 3) Jump to the hlt instruction if it ever wakes up due to a non-masklable interrupt occuring or due to system management mode.
    
    cli
.hang: hlt
    jmp .hang
.end:
