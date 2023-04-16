#include <srvos/interrupts.h>
#include <srvos/csr.h>
#include <srvos/panic.h>
extern void mtrap(void);
void init_interrupts(void) {
	CSRW("mtvec", mtrap);
	CSRW("mie", (1<<16)-1);
	// test interrupt
	// riscv doesn't interrupt on division by 0 unlike x86 so we use an ecall to test interrupts
	//int x = 1/0;
	asm volatile("ecall");
}

void handle_interrupt(void) {
	// placeholder for now
	panic("interrupt");
}
