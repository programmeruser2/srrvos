#ifndef INTERRUPTS_H
#define INTERRUPTS_H
#include <stdint.h>

typedef struct {
	uint64_t gpregs[32];
	void* trap_stack;
} trap_frame_t;

extern trap_frame_t kernel_trap_frame;

void init_interrupts(void);

#endif
