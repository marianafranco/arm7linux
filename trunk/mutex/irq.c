#include "irq.h"

// Installs a handler to the interruption vector
void irq_installhandler (unsigned routine, unsigned *vector) { 
	unsigned vec;
	// Checking if the function is in range
	vec = ((routine - (unsigned)vector - 0x8)>>2);
	vec = 0xea000000 | vec;
	*vector = vec;
}