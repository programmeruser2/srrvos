.PHONY: all qemu
sources = $(wildcard src/*.c) $(wildcard src/*.S)
all: kernel.elf
CFLAGS += -I include -g -nostdlib -fno-builtin -Wall -Wextra -ffreestanding -mcmodel=medany 
LDFLAGS += -T linker.ld
CC = riscv64-unknown-elf-gcc
kernel.elf: $(sources)
	$(CC) $(CFLAGS) $(LDFLAGS) $(sources) -o kernel.elf
qemu: all
	qemu-system-riscv64 -machine virt -bios none -kernel kernel.elf
