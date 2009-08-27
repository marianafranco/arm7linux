/* Setups IRQ registers and serives the IRQ's (timer) */
#include "cinit.h" // Remove after debug
//#include "macros.h"
#include "rpsarmul.h"

#define COUNTDOWN	0x00effff0 // Time for the timer

// Initialises the counter timer and sets the timer divisor.
/*void timer_init (void) {
  *TMOD		= 0;
  *INTPND 	= 0x00000000; 	// Clear pending interrupts
}*/

/* Interrupt service routine for timer0 interrupt.
   Timer interrupt everytime the counter reaches 0. To reset
   the timer TDATA0 has to have a new initialization value.
   Finally the last act is to unmask the timer interrupt */ 
/*void  timer_irq (void) { 
	// Reset timer interrupt
	*INTPND	= 1<<10;
	*TDATA0	= COUNTDOWN; 
	// Unmask the interrupt source
	*(volatile int*)INTMSK &= ~((1<<INT_GLOBAL)|(1<<10)|(1<<0));
} */

// Switches the timer on
/*void timer_start (void) {	
  	*TDATA0		 = COUNTDOWN;	// Load Counter Timer 
 	*TMOD 		|= 0x1;			// Enable interval interrupt
 	// Unmask the interrupt source
  	*(volatile int*)INTMSK &= ~((1 << INT_GLOBAL) | (1<<10) | (1<<0));     
}*/

void timer_init (void) {
	*IRQEnableClear = ~0; // Clear/disable all interrupts
	*Timer1Control = 0; // Disable counters by clearing the control bytes   
	*Timer1Clear = 0 ; // Clear counter/timer interrupts by writing to the clear register - any data will work
}

void timer_irq(void) {
	
	//cinit_print ("Interrupt!\n");
	*Timer1Clear = 0;/* clear the interrupt */
}

void timer_start (void) {	
  	*Timer1Load = COUNTDOWN; // Load counter values
	*Timer1Control = (TimerEnable | // Enable the Timer  )
					  TimerPeriodic | // Periodic Timer producing interrupt               
					  TimerPrescale8 ); // Set Maximum Prescale - 8 bits 
    *IRQEnableSet = IRQTimer1; // Enable the counter timer interrupts
}
	
