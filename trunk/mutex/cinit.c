/* Initialization code in C */

#include "cinit.h"

/* Entry point for C part */
int C_Entry (void) {
	/* Initialize 7-segment display */
	segment_init();
	/* Initialize timer */
	timer_init();
	/* Initialize button */
	button_init();
	/* Install hardware interruption handler */
	if (emulator == 1) {
		install_IRQ_handler ((unsigned)handler_emulator, (unsigned *)IRQVector);
	}
	else {
		install_IRQ_handler ((unsigned)handler, (unsigned *)IRQVector);
	}
	/* Install software interruption handler */
	install_SWI_handler ((unsigned)handler_swi, (unsigned *)SWIVector);
	/* Start timer */
	timer_start();
	/* Enabling IRQ interruption and changing to user mode */
	__asm {
		MOV		r1,	#0x40|0x10
		MSR 	CPSR_c, r1
	}
	/* Start with process 1 */
	task1();
	 /* The return below should not be reachable */
	return 0;
}