#include "timer.h"

// Initiate timer settings
void timer_init (void) {
	if (emulator == 1) {
	  *IRQEnableClear = ~0; // Clear/disable all interrupts
	  *EmulatorIRQTimerControl = 0; // Disable counters by clearing the control bytes   
	  *IRQTimerClear = 0 ; // Clear counter/timer interrupts by writing to the clear register - any data will work

	}
	else {
	  *TimerEnableSet		= 0;	// Disable interrupt
	  *IRQStatus 	= 0x00000000; 	// Clear pending interrupts 
	}
}

// Restart timer interrupt
void timer_irq(void) {
	if (emulator == 1) {
		*IRQTimerClear = 0;/* clear the interrupt */
	}
	else {
		*IRQStatus	= 1<<10;
		*EvaluatorIRQTimerLoad	= COUNTDOWN; 
		*(volatile int*)EvaluatorIRQTimerControl &= ~((1<<21)|(1<<10)|(1<<0));
	}
}	

// Start timer
void timer_start (void) {
	if (emulator == 1) {
  		*EmulatorIRQTimerLoad = COUNTDOWN; // Load counter values
		*EmulatorIRQTimerControl = (0x80 | // Enable the Timer
						  0x40 | // Periodic Timer producing interrupt               
						  0x08 ); // Set Maximum Prescale - 8 bits 
    	*IRQEnableSet = IRQTimer; // Enable interrupt
    }
    else {
    	*EvaluatorIRQTimerLoad		 = COUNTDOWN;	// Load counter values
    	*TimerEnableSet 		|= 0x1;			// Enable interrupt
    	*(volatile int*)EvaluatorIRQTimerControl &= ~((1 << 21) | (1<<10) | (1<<0)); // Unmask the interrupt source
	}
}
	
