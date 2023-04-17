#include <srvos/interrupts.h>
#include <srvos/csr.h>
#include <srvos/panic.h>
#include <srvos/alloc.h>
#include <stdint.h>

#include <srvos/console.h>
#define TRAP_STACK_SIZE 1024
trap_frame_t kernel_trap_frame;
extern void mtrap(void);
void init_interrupts(void) {
	// Set proper mscratch for interrupts
	//kernel_trap_frame.trap_stack = kmalloc(1024);
	kernel_trap_frame.trap_stack = ((uint8_t*) kmalloc(TRAP_STACK_SIZE)) + TRAP_STACK_SIZE - 1;
	CSRW("mscratch", &kernel_trap_frame);
	CSRW("mtvec", mtrap);
	CSRW("mie", (1<<16)-1);
	asm volatile("ecall");
	putline("done");
	//while (1);
}
int x=0;
uint8_t* handle_interrupt(void* epc, void* tval, size_t cause, size_t hart, size_t status, trap_frame_t frame) {
	printf("interrupt\n");
	printf("epc=%p, tval=%p, cause=%d, hart=%d, status=0x%x, trap frame=%p\n", epc, tval, cause, hart, status, frame);
	for (int i = 0; i < 32; ++i) {
		printf("x%d=0x%x\n", i, frame.gpregs[i]);
	}
	// placeholder for now
	++x;
	
  uint8_t* ret = ((uint8_t*)epc)+4;
	printf("ret=%p\n", ret);
/*if (x >= 2) {
	while(1) asm("");
	}*/
	return ret;
}
