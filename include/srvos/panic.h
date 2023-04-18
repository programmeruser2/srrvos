#ifndef PANIC_H
#define PANIC_H

#include <srvos/interrupts.h>
#define DUMP_REGS(frame) for (int _ = 0; _ < 8; ++_) { \
				for (int _1 = 0; _1 < 4; ++_1) { \
					printf("x%d = 0x%x ", _*4+_1, (frame).gpregs[_*4+_1]); \
				} \
				puts("\r\n"); \
	}
void panic(char* msg, ...);
void panic_frame(char* msg, trap_frame_t frame, ...);

#endif
