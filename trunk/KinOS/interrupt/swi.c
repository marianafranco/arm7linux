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
 
#include "swi.h"


/****************************************************************
 * ROUTINES
 ****************************************************************/

/* Calls the fork system call and return the child id or zero */ 
int fork(){
	int pid = 0;
	pid = syscall(0, 0, 0, 0);
	return pid; 
}

/* Calls the exec system call */
void exec(int process_id, pt2Task process_addr, int arg1){
	syscall(1, process_id, process_addr, arg1);
}

/* Calls the exit system call */
void exit(int process_id){
	syscall(2, process_id, 0, 0);
}

/* Calls the print system call */
void print(char *str) {
	syscall_print(3, 0, str, 0);
}

/* Calls the switch_thread system call */
void switch_thread (void) {
	syscall(4, 0, 0, 0);
}