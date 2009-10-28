#include "button.h"

void uHALir_UnmaskIrq(unsigned irq1,unsigned irq2) {
   *(volatile int*)INTMSK &= ~((1 << INT_GLOBAL) | (1<<irq1) | (1<<irq2));   /* Force global disable OFF */
}

void button_init (void) {	
		
	uHALir_UnmaskIrq(10,0);	

  *(unsigned *)IOPCON 	|= IO_ENABLE_INT0; 			// enable int0
  *(unsigned *)IOPCON	|= IO_ACTIVE_HIGH_INT0; 	// set as active high
  *(unsigned *)IOPCON	|= IO_RISING_EDGE_INT0;		// allow for RISING EDGE
}

void  button_irq (void) {	
	*(unsigned *) INTPND |= INT_SW3_MASK;

	// Faz algo
	
}