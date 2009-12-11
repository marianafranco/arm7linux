/* This file contains routines to initialize and handle button interruptions */

#include "button.h"

/* Initializes the button */
void button_init (void) {	
	/* Force global disable off */
	*(volatile int*)EvaluatorIRQTimerControl &= ~((1 << 21) | (1<<10) | (1<<0));
 	/* Enable int0 */
	*(unsigned *)IRQButtonControl |= 1 << 4;
 	/* Set as active high */
	*(unsigned *)IRQButtonControl |= 1 << 3;
	/* Allow for rising edge */
 	*(unsigned *)IRQButtonControl|= 1;
}

/* Handles a button interruption */
void  button_irq (void) {
	*(unsigned *) IRQStatus |= 1;

	/* Do something */
	run_end("all");		// Kill all tasks

}