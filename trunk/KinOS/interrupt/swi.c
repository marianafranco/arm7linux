#include "swi.h"


int fork(){
	int pid = 0;
	pid = syscall(0, 0, 0, 0);
	return pid; 
}

void exec(int process_id, pt2Task process_addr, int arg1){
	syscall(1, process_id, process_addr, arg1);
}

void exit(int process_id){
	syscall(2, process_id, 0, 0);
}

void print(char *str) {
	syscall_print(3, 0, str, 0);
}