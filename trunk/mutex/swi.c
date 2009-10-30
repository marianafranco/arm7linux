#include "swi.h"

extern int  Angel_SWI_Address;
extern void routine_fork(void);
extern void routine_exec(void);
extern void routine_exit(void);

void irq_installSWIhandler (unsigned routine, unsigned *vector) {

	if (emulator == 1) {
		unsigned vec;
		vec = ((routine - (unsigned)vector - 0x8)>>2);
		vec = 0xea000000 | vec;
		*vector = vec;
	}
	else {
		unsigned old_vector_value;
		unsigned *absolute;   
  		old_vector_value = 0;   
   		old_vector_value  = *vector;  	 // Get old vector contents ....................
   		old_vector_value ^= 0xe59ff000;	 // Mask off the instruction to get the offset

   		absolute	     	= (unsigned *)  (0x8+old_vector_value+0x8); 
					// SWI Address
   		Angel_SWI_Address 	= *absolute; 	// chain Angel Interrupt Handler	  
   		*absolute		= routine; 	// SWI handler
	}
}	

int fork(){
	syscall(0, 0, 0);
	return 0;
}

void exec(int process_id, pt2Task process_addr){
	syscall(1, process_id, process_addr);
}

void exit(){
	syscall(2, 0, 0);
}