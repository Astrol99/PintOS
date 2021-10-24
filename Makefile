# Find src files
C_SOURCES := $(shell find . -type f -name "*.c")
H_SOURCES := $(shell find . -type f -name "*.h")
ASM_SOURCES := $(shell find . -type f -name "*.asm")
C_OBJFILES := $(patsubst %.c,%.o,$(C_SOURCES))
ASM_OBJFILES := $(patsubst %.asm,%.o,$(ASM_SOURCES))
OBJFILES = $(ASM_OBJFILES) $(C_OBJFILES)

# Compilers
CC = i686-elf-gcc
AS = nasm

# Compiler options
WARNINGS := -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
            -Wwrite-strings \
            -Wredundant-decls -Wnested-externs -Winline -Wno-long-long \
            -Wstrict-prototypes
CFLAGS := -g -ffreestanding -nostdlib -O2 -std=gnu99 $(WARNINGS)
LDFLAGS = -T link.ld
ASFLAGS = -f elf

.PHONY: all run clean

all: kernel.elf

# Create kernel binary
kernel.elf: $(OBJFILES)
	$(CC) $(LDFLAGS) -o iso/boot/kernel.elf $(CFLAGS) $(OBJFILES) -lgcc

# Generate iso file of OS
PintOS.iso: kernel.elf
	grub-mkrescue -o PintOS.iso iso
	@grub-file --is-x86-multiboot iso/boot/kernel.elf || (echo "GRUB multiboot file check failed $$?"; exit 1)

# Run OS iso on qemu
run: PintOS.iso
	qemu-system-i386 -cdrom PintOS.iso -monitor stdio

# Debug OS using qemu and GDB
debug: PintOS.iso
	qemu-system-i386 -serial file:serial.log -s -S -cdrom PintOS.iso &
	gdb -ex "target remote localhost:1234" -ex "symbol-file iso/boot/kernel.elf" -ex "b kmain" -ex "continue"

# Compile all source files
%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@

clean:
	-$(RM) $(wildcard $(OBJFILES)) PintOS.iso serial.log iso/boot/kernel.elf
