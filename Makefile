SOURCES_CPP = $(wildcard *.cpp)

SOURCES_ASM = $(wildcard *.s)

OBJECTS = $(SOURCES_CPP:.cpp=.o) $(SOURCES_ASM:.s=.o)

CC = g++
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
         -nostartfiles -nodefaultlibs -fno-exceptions -fno-rtti \
         -fno-use-cxa-atexit -Wall -Wextra -Werror -c
LDFLAGS = -T link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf32

all: os.iso

kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o kernel.elf

os.iso: kernel.elf
	cp kernel.elf iso/boot/kernel.elf
	grub-mkrescue -o os.iso iso/

run: os.iso
	qemu-system-i386 -cdrom os.iso -serial stdio

%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@
	
%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf boot/*.o kernel/*.o kernel.elf os.iso 
