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

unsigned volatile int semaphore_shell	= 2; // this is a start value
unsigned volatile int semaphore_example	= 2; // this is a start value

void mutex_lock_shell (void) {

	__asm {
		spin:
		mov		r1, &semaphore_shell
		mov		r2, #1
		swp		r3,r2,[r1]
		cmp		r3,#1
		beq		spin
	}
}

void mutex_unlock_shell (void)  {
	__asm  {
		mov		r1, &semaphore_shell
		mov		r2, #0
		swp		r0,r2,[r1]
	}
}

void mutex_lock_example (void) {

	__asm {
		spin:
		mov		r1, &semaphore_example
		mov		r2, #1
		swp		r3,r2,[r1]
		cmp		r3,#1
		beq		spin
	}
}

void mutex_unlock_example (void)  {
	__asm  {
		mov		r1, &semaphore_example
		mov		r2, #0
		swp		r0,r2,[r1]
	}
}