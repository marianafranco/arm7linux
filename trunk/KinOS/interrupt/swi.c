#include "swi.h"

extern void routine_fork(void);
extern void routine_exec(void);
extern void routine_exit(void);

int fork(){
	int a = syscall(0, 0, 0);
	return a; 
}

void exec(int process_id, pt2Task process_addr){
	syscall(1, process_id, process_addr);
}

void exit(int process_id){
	syscall(2, process_id, 0);
}