CC = gcc
LD = ld

CFLAGS = -m32 -ffreestanding -fno-pie -fno-pic -c
LDFLAGS = -m elf_i386 -T linker.ld --oformat binary -nostdlib

all:
	nasm -f bin boot.asm -o boot.bin
	nasm -f elf32 kernel_entry.asm -o kernel_entry.o

	$(CC) $(CFLAGS) kernel.c -o kernel.o
	$(CC) $(CFLAGS) drivers/screen.c -o screen.o
	$(CC) $(CFLAGS) drivers/keyboard.c -o keyboard.o

	# Phase 6
	$(CC) $(CFLAGS) cpu/idt.c -o idt.o
	$(CC) $(CFLAGS) cpu/isr.c -o isr_c.o
	nasm -f elf32 cpu/isr.asm -o isr.o

	# Phase 7
	$(CC) $(CFLAGS) cpu/irq.c -o irq.o
	$(CC) $(CFLAGS) cpu/timer.c -o timer.o

	$(LD) $(LDFLAGS) \
	kernel_entry.o \
	kernel.o \
	screen.o \
	keyboard.o \
	idt.o \
	isr.o \
	isr_c.o \
	irq.o \
	timer.o \
	-o kernel.bin

	cat boot.bin kernel.bin > os.bin

run: all
	qemu-system-i386 -drive format=raw,file=os.bin

clean:
	rm -f *.o *.bin os.bin