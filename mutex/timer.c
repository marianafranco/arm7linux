/* Setups IRQ registers and serives the IRQ's (timer) */
#include "rpsarmul.h"

#define COUNTDOWN	0x00effff0 // Time for the timer

#define SYSCFG	0x03ff0000
#define TMOD				((volatile unsigned *)(SYSCFG+0x6000))
#define INTPND	((volatile unsigned *)(SYSCFG+0x4004))
#define TDATA0				((volatile unsigned *)(SYSCFG+0x6004))
#define INTMSK							((volatile unsigned *)(SYSCFG+0x4008))
#define INT_GLOBAL						(21)

void timer_init (void) {
//	*IRQEnableClear = ~0; // Clear/disable all interrupts
//	*Timer1Control = 0; // Disable counters by clearing the control bytes   
//	*Timer1Clear = 0 ; // Clear counter/timer interrupts by writing to the clear register - any data will work
  *TMOD		= 0;
  *INTPND 	= 0x00000000; 	// Clear pending interrupts 
}

void timer_irq(void) {
	
//	*Timer1Clear = 0;/* clear the interrupt */
		*INTPND	= 1<<10;
	*TDATA0	= COUNTDOWN; 
	*(volatile int*)INTMSK &= ~((1<<INT_GLOBAL)|(1<<10)|(1<<0));
}

void timer_start (void) {	
  	//*Timer1Load = COUNTDOWN; // Load counter values
	//*Timer1Control = (TimerEnable | // Enable the Timer  )
	//				  TimerPeriodic | // Periodic Timer producing interrupt               
	//				  TimerPrescale8 ); // Set Maximum Prescale - 8 bits 
    //*IRQEnableSet = IRQTimer1; // Enable the counter timer interrupts
    
    *TDATA0		 = COUNTDOWN;	// load Counter Timer 
    *TMOD 		|= 0x1;			// enable interval interrupt 	
    *(volatile int*)INTMSK &= ~((1 << INT_GLOBAL) | (1<<10) | (1<<0)); //unmask the interrupt source
}
	
