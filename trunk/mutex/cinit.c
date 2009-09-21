#include "tasks.h"
#include "timer.h"
#include "irq.h"
#include "segment.h"
#include "rpsarmul.h"

extern void handler(void);

// Entry point for the program 
int C_Entry ( void ) {	
	// Initialize 7-segment display
	segment_init();
	// Initialize timer
	timer_init 	();
	// Install handler
	irq_installhandler ((unsigned)handler, (unsigned *)IRQVector);
	// Start timer
	timer_start ();
	// Enabling IRQ interruption, changing to user mode
	__asm {
		MOV		r1,	#0x40|0x10
		MSR CPSR_c, r1
	}
	// Start with process 1
	task1();
	 // This return is not reachable
	return 0;
}