/* C functions for hardware interruptions */

#include "irq.h"

/* Reserved spaces where the Angel IRQ/SWI addressess will be stored */
extern int  Angel_IRQ_Address;
extern int  Angel_SWI_Address;

/* 	Installs a handler branch on the interrupt vector */
void install_handler (unsigned handler_routine_address, unsigned *vector_address) {

	/* Case it is running in the emulator or without angel */
	if (emulator == 1 || emulator == 2) {
		/* The instruction that will be put in the IRQ vector */
		unsigned branch_to_handler_instruction;
		/* Handler relative address */
		unsigned offset;
		/* -0x8 due to the pipeline, >> 2 due to the word alignment */
		offset = ((handler_routine_address - (unsigned)vector_address - 0x8) >> 2);
		/* Add to the address, the branch instruction */
		branch_to_handler_instruction = 0xea000000 | offset;
		/* Put the instruction in the vector */
		*vector_address = branch_to_handler_instruction;
	}
	/* Case it is running with the angel */
	else {
		/* Angel branch instruction */
		unsigned Angel_branch_instruction;
		/* Angel instruction */
		unsigned *Angel_address;
		/* Getting Angel branch instruction */		
		Angel_branch_instruction  = *vector_address;
   		/* Separate the instruction from the address */
		Angel_branch_instruction ^= 0xe59ff000;
		/* Calculating absolute address */
		Angel_address = (unsigned *) ((unsigned)vector_address + Angel_branch_instruction + 0x8);
		/* Store address in the propoer position */
		if ((unsigned)vector_address == 0x18) {
			Angel_IRQ_Address = *Angel_address;
		}
		else {
			Angel_SWI_Address = *Angel_address;
		}
		/* Inserting handler instruction in the vector table */
   		*Angel_address = handler_routine_address;
	}
}