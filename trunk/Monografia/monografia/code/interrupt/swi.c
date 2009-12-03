#include "swi.h"

extern void routine_fork(void);
extern void routine_exec(void);
extern void routine_exit(void);

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