OBJECTS = utils/string.o drivers/output.o drivers/io.o kernel/kmain.o loader.o

# Check if OSX
os = $(shell uname -s) 

CC = $(if $(filter Darwin, $(os)), i686-elf-gcc, gcc)
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
			-nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c

LD = $(if $(filter Darwin, $(os)), i686-elf-ld, ld)
LDFLAGS = -T link.ld -melf_i386

AS = nasm
ASFLAGS = -f elf32

ISO_MAKER = $(if $(filter Darwin, $(os)), mkisofs, genisoimage)
QEMU = $(if $(filter Darwin, $(os)), qemu-system-i386, qemu-system-i386.exe)
BOCHS = $(if $(filter Darwin, $(os)), bochs, bochs.exe)
BOCHS_CONFIG = $(if $(filter Darwin, $(os)), ../bochsrc_osx.txt, ../bochsrc_wsl.txt)

GDB = gdb

all: kernel.elf

kernel.elf: $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) -o iso/boot/kernel.elf

os.iso: kernel.elf
	$(ISO_MAKER) -R                              \
				-b boot/grub/stage2_eltorito    \
				-no-emul-boot                   \
				-boot-load-size 4               \
				-A os                           \
				-input-charset utf8             \
				-quiet                          \
				-boot-info-table                \
				-o os.iso                       \
				iso

run: os.iso
	$(QEMU) -boot d -cdrom os.iso -m 10240 -monitor stdio -s

run-bochs: os.iso
	$(BOCHS) -f $(BOCHS_CONFIG) -q

%.o: %.c
	$(CC) $(CFLAGS)  $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf *.o */*.o iso/boot/kernel.elf os.iso bochslog.txt
