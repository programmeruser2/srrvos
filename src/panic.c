#include <srvos/panic.h>
#include <srvos/console.h>
#include <srvos/interrupts.h>
#include <stdarg.h>

void panic(char* msg, ...) {
	putline("--- KERNEL PANIC ---");
	va_list ap;
	va_start(ap, msg);
	vprintf(msg, ap);
	while (1);
}

void panic_frame(char* msg, trap_frame_t frame, ...) {
	putline("--- KERNEL PANIC ---");
	va_list ap;
	va_start(ap, frame);
	vprintf(msg, ap);
	putline("-- Registers: --");
	DUMP_REGS(frame);
	while (1);
}
