.align 4
.global mtrap
.type mtrap, @function

.altmacro
.macro save_gpreg i, base=t6
	sd x\i, ((\i)*8)(base)
.endm

.macro save_fpreg i, base=t6
	fsd f\i, ((32+(\i))*8)(base)
.endm

.macro load_gpreg i, base=t6
	ld x\i, ((\i)*8)(base)
.endm

.macro load_fpreg i, base=t6
	fld f\i, ((32+(\i))*8)(base)
.endm

mtrap:
	// TODO: maybe use supervisor mode to avoid risk of stack overwrites with mscratch stack?
	// Save old t6 value
	csrrw t6, mscratch, t6
	// Load all general purpose registers
	.set i, 0
	.rept 31
		save_gpreg %i
		.set i, i+1
	.endr
	// save t6 (x31) separately
	// we move to t5 to take advantage of save_gpreg
	mv t5, t6
	csrr t6, mscratch
	save_gpreg 31, t5
	// TODO: handle floating point regs?
	// save trap frame since handle_interrupt may overwrite t5
	csrw mscratch, t5

	// call with all relevant info
	csrr a0, mepc
	csrr a1, mtval
	csrr a2, mcause
	csrr a3, mhartid
	csrr a4, mstatus
	mv a5, t5
	ld sp, 256(a5)
	
	call handle_interrupt
	// return address
	csrw mepc, a0
	// restore
	csrr t6, mscratch
	.set i, 1
	.rept 31
		load_gpreg %i
		.set i, i+1
	.endr
	mret
