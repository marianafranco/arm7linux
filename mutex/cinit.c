/* The C Initializer is designed to initialize the interrupts 
   and set off task A. */

#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "tasks.h"
#include "timer.h"
#include "irq.h"
#define		angel_SWI	0x123456

// Angel SWI Note: remove if program is for standalone mode
__swi (angel_SWI) void _WriteC(unsigned op, const char *c);
#define WriteC(c) _WriteC (0x3,c)


// Prints information out to the console of the debugger 
void cinit_print (const char *string) { 
int pos = 0;
	  while (string[pos] != 0) WriteC(&string[pos++]);
}

void cinit_banner (void) {
	// Banner
	//cinit_print ("\n  Remove the serial cable from the board \n");	
	//cinit_print ("    Remember to RESET the board after USE \n");
	segment_init();
}

/* Initializes the LED's on the Evaluator7T board to be 
   OFF. Setup the internal GLOBALS to indicate that the 
   LED's are OFF. */
void cinit_init (void) {
	// Init hardware
	cinit_banner 	();
	irq_init  		();
	timer_start 	();
}

// Entry point for tasker 
int C_Entry ( void ) {	
	// Initialize all internal structures
	cinit_init    	();
	// Enabling IRQ interruptions
	/*__asm {
	MRS			r1,CPSR
	ORR			r1,r1,#0x10
	MSR 		CPSR_c,r1
	}*/
	__asm {
		MRS r1, CPSR
		BIC r1, r1, #0x80
		ORR	r1,	r1,	#0x10
		MSR CPSR_c, r1
	}
	task1();  // Start with process 1
	// Should never reach this return
	return 0;
}