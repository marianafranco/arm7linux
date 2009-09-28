#include "swi.h"

extern int  Angel_SWI_Address;

__swi(fork_SWI) void _fork(int process);
__swi(exec_SWI) void _exec(int);
__swi(exit_SWI) void _exit(int);
#define fork(process) _fork (process)
#define exec(process) _exec (process)
#define exit(process) _exit (process)
	
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

void rotina_fork (int processo) {
	if (processo == 1) {
		//LED_1_ON;
	}
}

void rotina_exec (int processo) {
	if (processo == 1) {
		//LED_2_ON;
	}
}

void rotina_exit (int processo) {
	if (processo == 1) {
		//LED_3_ON;
	}
}

void swi_chandler (unsigned swi_number, int processo) {

	switch (swi_number) {
		case fork_SWI:
			rotina_fork(processo);
			break;
		case exec_SWI:
			rotina_exec(processo);
			break;
		default:
			rotina_exit(processo);
			break;	
	}	
}	