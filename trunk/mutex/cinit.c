#include "tasks.h"
#include "timer.h"
#include "irq.h"
#include "button.h"
#include "segment.h"
#include "swi.h"
#include "rpsarmul.h"

extern void handler(void);
extern void handler_swi(void);
extern void handler_emulator(void);

// Entry point for the program 
int C_Entry ( void ) {	
	// Initialize 7-segment display
	segment_init();
	// Initialize timer
	timer_init 	();
	// Initialize button
	button_init ();
	// Install handler
	if (emulator == 1) {
		irq_installhandler ((unsigned)handler_emulator, (unsigned *)IRQVector);
	}
	else {
		irq_installhandler ((unsigned)handler, (unsigned *)IRQVector);
	}
	irq_installSWIhandler ((unsigned)handler_swi, SWIVector);
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