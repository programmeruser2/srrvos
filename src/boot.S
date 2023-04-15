.section .text.init
// fsr _start has to be placed at the start of .text or qemu won't load it??? idk
.type start, @function
.global _start
_start:
	la gp, __global_pointer
	// setup stack
	la sp, __stack
	// setup bss
	la t0, __bss_start
	sd x0, 0(t0)
	la t1, __bss_end
	.clear_bss:
		addi t0, t0, 8
		sd x0, 0(t0)
		bltu t0, t1, .clear_bss 
	// jump to main
	tail kmain
	.loop: j .loop
