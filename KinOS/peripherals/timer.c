/************************************************************************************
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
*************************************************************************************/


/* This file contains routines to initialize and handle timer interruptions */

#include "timer.h"

/* Initiate timer settings */
void timer_init (void) {
	/* Case it's from the emulator */
	if (emulator == 1) {
		/* Clear/disable all interrupts */
	  	*IRQEnableClear = ~0; 
		/* Disable counters by clearing the control bytes */  
	  	*EmulatorIRQTimerControl = 0; 
		/* Clear counter/timer interrupts  */
	  	*IRQTimerClear = 0 ; 
	}
	/* Case it's the board */
	else {
		/* Disable interrupt */
		*TimerEnableSet	= 0;
		 /* Clear pending interrupts */
	  	*IRQStatus = 0x00000000;
	}
}

/* Restart timer interrupt */
void timer_irq(void) {
	if (emulator == 1) {
		/* Clear the interrupt */
		*IRQTimerClear = 0;
	}
	else {
		/* Clear pending interrupts */
		*IRQStatus	= 1 << 10;
		/* Load counter values */
		*EvaluatorIRQTimerLoad = COUNTDOWN; 
		/* Unmask the interrupt source */
		*(volatile int*)EvaluatorIRQTimerControl &= ~((1<<21) | (1<<10) | (1<<0));
	}
}	

/* Start timer */
void timer_start (void) {
	if (emulator == 1) {
		/* Load counter values */
  		*EmulatorIRQTimerLoad = COUNTDOWN; 
		/* Enable the Timer | Periodic Timer producing interrupt | Set Maximum Prescale - 8 bits */
		*EmulatorIRQTimerControl = (0x80 | 0x40 | 0x08 ); 
		/* Enable interrupt */
    	*IRQEnableSet = IRQTimer; 
    }
    else {
		/* Load counter values */
    	*EvaluatorIRQTimerLoad = COUNTDOWN;	
		/* Enable interrupt */
    	*TimerEnableSet |= 0x1;			
		/* Unmask the interrupt source */
    	*(volatile int*)EvaluatorIRQTimerControl &= ~((1 << 21) | (1 << 10) | (1 << 0)); 
	}
}
	
