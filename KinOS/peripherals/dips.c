/************************************************************************************
	KinOS - Microkernel for ARM Evaluator 7-T
	Seniors project - Computer Engineering
	Escola Politecnica da USP, 2009
	
	Felipe Giunte Yoshida
	Mariana Ramos Franco
	Vinicius Tosta Ribeiro
*/

/* 
	The program was based on the mutex program by ARM - Strategic Support Group,
	contained on the ARM Evaluator 7-T example CD, under the folder /Evaluator7-T/
	source/examples/mutex/ 
*************************************************************************************/


/****************************************************************
 * IMPORT
 ****************************************************************/

/* This file contains routines to initialize and handle DIPS interruptions */

#include "dips.h"


/****************************************************************
 * ROUTINES
 ****************************************************************/
 
/* Return the value of the dip switches */
unsigned dips_read (void) 
{
	/* 0xf = switch mask */
	return 0xF & *IOData; 
}
