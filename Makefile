 OBJECTS = loader.o kmain.o
CC = g++
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
         -nostartfiles -nodefaultlibs -fno-exceptions -fno-rtti \
         -fno-use-cxa-atexit -Wall -Wextra -Werror -c
LDFLAGS = -T linker.ld -melf_i386
AS = nasm
ASFLAGS = -f elf32

all: os.iso

kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o kernel.elf

os.iso: kernel.elf
	cp kernel.elf iso/boot/kernel.elf
	grub-mkrescue -o os.iso iso/

run: os.iso
	qemu-system-i386 -cdrom os.iso

%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

%.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf boot/*.o kernel/*.o kernel.elf os.iso 
