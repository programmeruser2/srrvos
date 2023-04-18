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
	//asm volatile("ecall");
	asm volatile("la t0, 0\nlb t0, 0(t0)");
	putline("done");
	//while (1);
}

uint8_t* handle_interrupt(void* epc, void* tval, size_t cause, size_t hart, size_t status, trap_frame_t frame) {
	size_t cause_num = cause & 0xfff;
	(void)status;
	if (((cause >> 63) & 1) == 1) {
		// async interrupt
		// TODO: what to do on unknown trap?
		switch (cause_num) {
			default:
				break;
		}
	} else {
		// sync interrupt
		switch (cause_num) {
			case 0:
			panic_frame("Instruction address misaligned on CPU#%d; %p -> 0x%x, mstatus=0x%x\n", frame, hart, epc, tval, status);
				break;
			case 1:
				panic_frame("Instruction address fault on CPU#%d; %p -> 0x%x, mstatus=0x%x\n", frame, hart, epc, tval, status);
				break;
			case 2:
				panic_frame("Illegal instruction on CPU#%d; %p -> 0x%x, mstatus=0x%x\n", frame, hart, epc, tval, status);
				break;
			case 3:
				panic_frame("Load address misaligned on CPU#%d; %p -> 0x%x, mstatus=0x%x\n", frame, hart, epc, tval, status);
				break;
			case 4:
				panic_frame("Load address fault on CPU#%d; %p -> 0x%x, mstatus=0x%x\n", frame, hart, epc, tval, status);
				break;
			case 5:
				panic_frame("Load access fault on CPU#%d; %p -> 0x%x, mstatus=0x%x\n", frame, hart, epc, tval, status);
				break;
			default:
				break;
		}
	}
  uint8_t* ret = ((uint8_t*)epc)+4;
	return ret;
}
