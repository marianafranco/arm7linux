/* C functions for hardware interruptions */

#include "irq.h"

/* Reserved space where the Angel IRQ address will be stored */
extern int  Angel_IRQ_Address;

/* 	Installs a handler branch on the interrupt vector */
void install_IRQ_handler (unsigned handler_routine_address, unsigned *irq_vector_address) {

	/* Case it is running in the emulator */
	if (emulator == 1) {
		/* The instruction that will be put in the IRQ vector */
		unsigned branch_to_handler_instruction;
		/*  */
		branch_to_handler_instruction = ((handler_routine_address - (unsigned)irq_vector_address - 0x8) >> 2);
		/* Add to the address, the branch instruction */
		branch_to_handler_instruction = 0xea000000 | branch_to_handler_instruction;
		/* Put the instruction in the vector */
		*irq_vector_address = branch_to_handler_instruction;
	}
	/* Case it is running on the board */
	else {
		/* Angel routine address */
		unsigned Angel_address;
		/*  */
		unsigned *segundo;
		/*  */
		Angel_address  = *irq_vector_address;
   		/* Separate the instruction from the address */
		Angel_address ^= 0xe59ff000;
		/*  */
		segundo = (unsigned *) (0x18 + Angel_address + 0x8);
		/*  */
		Angel_IRQ_Address = *segundo;
		/*  */
   		*segundo = handler_routine_address;
	}
}