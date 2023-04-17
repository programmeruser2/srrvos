#include <srvos/console.h>
#include <srvos/string.h>
#include <srvos/alloc.h>
#include <srvos/interrupts.h>
extern unsigned char __heap_start;
void kmain(void) {
	putline("Hello kernel world!");
	putline("initializing heap");
	init_heap();
	/*char* buf = kmalloc(1024);
	printf("%p %p %p %d %x %p %p", buf, &__heap_start, GET_HEADER(buf), GET_HEADER(buf)->state, GET_HEADER(buf)->size, GET_HEADER(buf)->prev, GET_HEADER(buf)->next);
	while(1) asm("");*/
	putline("init interrupts");
	init_interrupts();
	//while(1);		
	putline("returned");
}
