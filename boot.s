/* Multiboot header constants */
.set ALIGN,     1<<0            /* align loaded modules on page boundaries */
.set MEMINFO,   1<<1            /* provide memory map */
.set FLAGS,     ALIGN | MEMINFO /* Multiboot 'flag' field */
.set MAGIC,     0x1BADB002      /* 'magic number' lets bootloader find header */
.set CHECKSUM,  -(MAGIC + FLAGS)/* Checksum of above to prove we are multiboot */

/* Declaring a multiboot header to mark program as a kernel */
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

/* Create stack pointer register */
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

.section .text
.global _start
.type _start, @function
_start:
    /* Kernel now has full absolute control of the CPU */

    /* Set ESP register to point to the top of the created stack (grows downward on x86) for C */
    mov $stack_top, %esp

    /* Initalize curcial processor state (TODO) */

    /* Enter high-level kernel (C) */
    call kernel_main

    /* Infinite loop when computer has nothing to do
    1) Disable interrupts with cli
    2) Wait for next interrupt to arrive with hlt instruction (will lock up computer to it being disabled)
    3) Jump to the hlt instruction if it ever wakes up due to a non-masklable interrupt occuring or due to system management mode.
    */
    cli
1:  hlt
    jmp 1b

/* Set size of _start sumbol to current location minus start for debugging or call tracing */
.size _start, . - _start
