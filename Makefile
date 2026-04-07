CC = gcc
LD = ld

CFLAGS = -m32 -ffreestanding -fno-pie -fno-pic -c
LDFLAGS = -m elf_i386 -T linker.ld --oformat binary -nostdlib

all:
	nasm -f bin boot.asm -o boot.bin
	nasm -f elf32 kernel_entry.asm -o kernel_entry.o

	$(CC) $(CFLAGS) kernel.c -o kernel.o
	$(CC) $(CFLAGS) drivers/screen.c -o screen.o

	# ---------- PHASE 6 ADD HERE ----------
	$(CC) $(CFLAGS) cpu/idt.c -o idt.o
	$(CC) $(CFLAGS) cpu/isr.c -o isr_c.o
	nasm -f elf32 cpu/isr.asm -o isr.o
	# --------------------------------------

	$(LD) $(LDFLAGS) \
	kernel_entry.o \
	kernel.o \
	screen.o \
	idt.o \
	isr.o \
	isr_c.o \
	-o kernel.bin

	cat boot.bin kernel.bin > os.bin

run: all
	qemu-system-i386 -drive format=raw,file=os.bin

clean:
	rm -f *.o *.bin os.bin
