/* Bootloader will look at image and start exec at symbol designated as entry point */
ENTRY(_start)

/* Tell where various sections of object files will be put in final kernel image */
SECTIONS
{
    /* Put sections at 1 MiB, best place for kernels to be loaded at by bootloader */
    . = 1M;

    /* First put multiboot header to be properly recognized as well as .text section */
    .text BLOCK(4K) : ALIGN(4K)
    {
        *(.multiboot)
        *(.text)
    }

    /* Read-only data */
    .rodata BLOCK(4K) : ALIGN(4K)
    {
        *(.rodata)
    }

    /* Read-write data (initalized) */
    .data BLOCK(4K) : ALIGN(4K)
    {
        *(.data)
    }

    /* Read-write data (uninitialized) and stack */
    .bss BLOCK(4K) : ALIGN(4K)
    {
        *(COMMON)
        *(.bss)
    }
}