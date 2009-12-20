/****************************************************************
 * IMPORT
 ****************************************************************/

#include "timer.h"


/****************************************************************
 * ROUTINES
 ****************************************************************/
 
/* 	Installs a handler branch on the interrupt vector */
void install_handler (unsigned handler_routine_address, unsigned *vector_address);