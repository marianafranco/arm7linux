#include "irq.h"

extern int  Angel_IRQ_Address;

// Installs a handler to the interruption vector
void irq_installhandler (unsigned routine, unsigned *vector) { 
	
	/*unsigned vec;
	// Checking if the function is in range
	vec = ((routine - (unsigned)vector - 0x8)>>2);
	vec = 0xea000000 | vec;
	*vector = vec;
	*/
	
	unsigned old_vector_value = 0;
	unsigned *segundo;
  
   	old_vector_value = 0;
  	old_vector_value  = *vector;
   	old_vector_value ^= 0xe59ff000;

   	segundo = (unsigned *) (0x18 + old_vector_value+0x8); 
			
   	Angel_IRQ_Address = *segundo;	  
   	*segundo = routine;
	
}