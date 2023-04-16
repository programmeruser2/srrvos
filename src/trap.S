.align 4
.global mtrap
.type mtrap, @function

mtrap:
	j handle_interrupt
	mret
