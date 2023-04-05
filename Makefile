.PHONY: all qemu
sources := $(wildcard src/*.c) $(wildcard src/*.S)
all: kernel.elf
kernel.elf: $(sources)
	riscv64-unknown-elf-gcc -T linker.ld -g -nostdlib $(sources) -o kernel.elf
qemu: all
	qemu-system-riscv64 -machine virt -bios none -kernel kernel.elf
