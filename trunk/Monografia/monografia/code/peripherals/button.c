/****************************************************************
	KinOS - Microkernel for ARM Evaluator 7-T
	Seniors project - Computer Engineering
	Escola Politecnica da USP, 2009
	
	Felipe Giunte Yoshida
	Mariana Ramos Franco
	Vinicius Tosta Ribeiro
*/

/* 
	The program was based on the mutex program by ARM - Strategic Support Group,
	contained on the ARM Evaluator 7-T example CD, under the folder /Evaluator7-T/
	source/examples/mutex/ 
*****************************************************************/


/****************************************************************
 * IMPORT
 ****************************************************************/

/* This file contains routines to initialize and handle button interruptions */

#include "button.h"


/****************************************************************
 * ROUTINES
 ****************************************************************/
 
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
	
	/* Call the function to kill all tasks with pid > 1 */
	print("\r\n");
	run_end("all");

}