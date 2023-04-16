#include <srvos/console.h>
#include <srvos/string.h>
#include <srvos/alloc.h>
#include <srvos/interrupts.h>
extern unsigned char __heap_start;
void kmain(void) {
	putline("Hello kernel world!");
	putline("initializing heap");
	init_heap();

	putline("init interrupts");
	init_interrupts();
		
}
