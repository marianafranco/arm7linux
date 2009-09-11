/* Installs an IRQ handler and initializes the timer interrupt */
#include "timer.h"
#include "rpsarmul.h"

extern void handler_timer(void);

// Installs a handler to the interruption vector
void irq_installhandler (unsigned routine, unsigned *vector) { 
	unsigned vec;
	// Checking if the function is in range
	vec = ((routine - (unsigned)vector - 0x8)>>2);
	if (vec & 0xff000000) {
		int error = 1 / 0;
		error = error;
	}
	vec = 0xea000000 | vec;
	*vector = vec;
	
	//unsigned old_vector_value = 0;
	//unsigned *vector;   
   //old_vector_value = 0;
   //old_vector_value  = *vector;  	 // Get old vector contents ....................
   //old_vector_value ^= 0xe59ff000;	 // Mask off the instruction to get the offset
   //vector	     	= (unsigned *) (0x18 + old_vector_value+0x8);
   //Angel_IRQ_Address 	= *vector; 	// chain Angel Interrupt Handler	  
  // *vector		= routine; 	// IRQ handler
}

// Initializes all the IRQ interrupt and installs an IRQ handler.
void irq_init (void) {
	// Initializes timer
	timer_init 	();
	// Install handler
	irq_installhandler ((unsigned)handler_timer, (unsigned *)IRQVector);
}
