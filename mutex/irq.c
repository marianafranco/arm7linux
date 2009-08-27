#include <stdio.h>
#include <stdlib.h>
#include "stand_i.h"
#include "cinit.h"

/* Installs an IRQ handler and initializes the timer interrupt */
#include "timer.h"
//#include "macros.h"
#include "rpsarmul.h"

extern void handler_timer(void);
extern int  Angel_IRQ_Address;

/* Places a branch instruction for the routine into the defined 
 * 'vector' location - this function returns the original 
 * contents of the 'vector      
 * Parameters   : unsigned routine - IRQ handler
 *				: unsigned *vector - IRQ vector   
 * Notes        : 'routine' MUST BE WITHIN A  RANGE OF 32Mbytes FROM 'vector' */
/*static void irq_installhandler (unsigned routine, unsigned *vector)  {
	unsigned old_vector_value = 0;
	unsigned *absolute;   
   old_vector_value = 0;
   // Now the inverse must be done on the original vector to retrieve 
   //the Angel IRQ Handler routine 
   // Get old vector contents
   old_vector_value  = *vector;
   // Mask off the instruction to get the offset
   old_vector_value ^= 0xe59ff000;
   // Calculate absolute address
   absolute	     	= (unsigned *) (0x18 + old_vector_value+0x8); 
   // IRQ Address
   Angel_IRQ_Address 	= *absolute; 	// chain Angel Interrupt Handler	  
   // IRQ handler
   *absolute		= routine; 
}*/

unsigned irq_installhandler (unsigned routine, unsigned *vector) { 
	unsigned vec, oldvec;
	vec = ((routine - (unsigned)vector - 0x8)>>2);
	if (vec & 0xff000000) {
		//printf ("Installation of Handler failed");
		//exit(1);
		vec = 0x0;
	}
	vec = 0xea000000 | vec;
	oldvec = *vector;
	*vector = vec;
	return (oldvec);
}

// Initializes all the IRQ interrupt and installs an IRQ handler.
void irq_init (void) {
	// Initializes timer
	timer_init 	();
	// Install handler
	irq_installhandler ((unsigned)handler_timer, (unsigned *)IRQVector);
	//irq_installhandler ((unsigned)timer_irq, (unsigned *)IRQVector);
}
