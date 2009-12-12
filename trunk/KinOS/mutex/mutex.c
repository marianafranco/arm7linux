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


/******************************************************************
 * STATICS
 ******************************************************************/
 
unsigned volatile int semaphore	= 2; // this is a start value


/******************************************************************
 * ROUTINES
 ******************************************************************/
 
 
/* -- mutex_gatelock ----------------------------------------------
 *
 * Description 	: Locks the semaphore... 
 * 
 * Parameters	: none...
 * Return		: none...
 * Notes		:
 *
 */
 
void mutex_gatelock (void) {
	__asm {
		spin:
		mov		r1, &semaphore
		mov		r2, #1
		swp		r3,r2,[r1]
		cmp		r3,#1
		beq		spin
	}
}


/* -- mutex_gateunlock -------------------------------------------
 *
 * Description 	: Unlocks the semaphore ...
 * 
 * Parameters	: none...
 * Return		: none...
 * Notes		:
 *
 */

void mutex_gateunlock (void)  {
	__asm  {
		mov		r1, &semaphore
		mov		r2, #0
		swp		r0,r2,[r1]
	}
}