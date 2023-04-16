#include <srvos/interrupts.h>
#include <srvos/csr.h>
#include <srvos/panic.h>
#include <srvos/alloc.h>

trap_frame_t kernel_trap_frame;
extern void mtrap(void);
void init_interrupts(void) {
	// Set proper mscratch for interrupts
	kernel_trap_frame.trap_stack = kmalloc(1024);
	CSRW("mscratch", &kernel_trap_frame);
	CSRW("mtvec", mtrap);
	CSRW("mie", (1<<16)-1);
	asm volatile("ecall");
}

void handle_interrupt(void* epc, void* tval, size_t cause, size_t hart, size_t status, trap_frame_t frame) {
	// placeholder for now
	panic("interrupt");
}
