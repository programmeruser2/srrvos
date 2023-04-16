#include <srvos/console.h>
#include <srvos/string.h>
#include <srvos/alloc.h>
#include <srvos/interrupts.h>
extern unsigned char __heap_start;
void kmain(void) {
	putline("Hello kernel world!");
	char n[20];
	itoa(-12345, n, 10);
	putline(n);
	putline("init interrupts");
	init_interrupts();
	putline("initializing heap");
	init_heap();
	putline("Allocating 10 bytes of memory @ heap");
	unsigned char* buf = kmalloc(10);
	puts("distance from __heap_start: 0x");
	itoa((void*) buf - (void*)&__heap_start, n, 16);
	putline(n);
	putline("done");
}
