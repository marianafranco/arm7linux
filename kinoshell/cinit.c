/* The program was based on the mutex program by ARM - Strategic Support Group,
contained on the ARM Evaluator 7-T example CD, under the folder /Evaluator7-T/
source/examples/mutex/ */

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
		install_handler ((unsigned)handler_emulator, (unsigned *)IRQVector);
	}
	else {
		install_handler ((unsigned)handler_board, (unsigned *)IRQVector);
	}
	/* Install software interruption handler */
	install_handler ((unsigned)handler_swi, (unsigned *)SWIVector);
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