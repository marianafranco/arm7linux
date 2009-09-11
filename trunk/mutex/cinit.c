/* The C Initializer is designed to initialize the interrupts 
   and set off task A. */

#include "tasks.h"
#include "timer.h"
#include "irq.h"

// Init hardware 
void cinit_init (void) {
	segment_init();
	irq_init ();
	timer_start ();
}

// Entry point for tasker 
int C_Entry ( void ) {	
	// Initialize all internal structures
	cinit_init    	();
	// Enabling IRQ interruptions
	__asm {
		MRS r1, CPSR
		BIC r1, r1, #0x80
		ORR	r1,	r1,	#0x10
		MSR CPSR_c, r1
	}
	task1();  // Start with process 1
	return 0; // Should never reach this return
}