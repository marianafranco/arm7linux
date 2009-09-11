/* Setups IRQ registers and serives the IRQ's (timer) */
#include "rpsarmul.h"

#define COUNTDOWN	0x00cffff0 // Time for the timer 0x00effff0

void timer_init (void) {
	if (emulator == 1) {
	  *IRQEnableClear = ~0; // Clear/disable all interrupts
	  *Timer1Control = 0; // Disable counters by clearing the control bytes   
	  *Timer1Clear = 0 ; // Clear counter/timer interrupts by writing to the clear register - any data will work

	}
	else {
	  *TMOD		= 0;
	  *INTPND 	= 0x00000000; 	// Clear pending interrupts 
	}
}

void timer_irq(void) {
	if (emulator == 1) {
		*Timer1Clear = 0;/* clear the interrupt */
	}
	else {
		*INTPND	= 1<<10;
		*TDATA0	= COUNTDOWN; 
		*(volatile int*)INTMSK &= ~((1<<INT_GLOBAL)|(1<<10)|(1<<0));
	}
}	

void timer_start (void) {
	if (emulator == 1) {
  		*Timer1Load = COUNTDOWN; // Load counter values
		*Timer1Control = (TimerEnable | // Enable the Timer  )
						  TimerPeriodic | // Periodic Timer producing interrupt               
						  TimerPrescale8 ); // Set Maximum Prescale - 8 bits 
    	*IRQEnableSet = IRQTimer1; // Enable the counter timer interrupts
    }
    else {
    	*TDATA0		 = COUNTDOWN;	// load Counter Timer 
    	*TMOD 		|= 0x1;			// enable interval interrupt 	
    	*(volatile int*)INTMSK &= ~((1 << INT_GLOBAL) | (1<<10) | (1<<0)); //unmask the interrupt source
	}
}
	
