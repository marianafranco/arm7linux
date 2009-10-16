#include "tasks.h"
#include "swi.h"
#include <string.h>



struct { char* name; void (*task_ptr)(void); } tasks_name[] = {
	{"task1", &task1},
	{"task2", &task2}
};


pt2Task  get_task_addr(char* name){
	int i;
	for(i=0; i<sizeof(tasks_name); i++){
		if(strcmp(tasks_name[i].name, name)==0){
			return tasks_name[i].task_ptr;
		}
	
	}
	return NULL;
}


void task1 (void) {
	
	char* newTask = "task2";
	exec(2, get_task_addr(newTask));
	
	while (1) {
		segment_set(1);
	}
}

void task2 (void) {
	while (1) {
		segment_set(2);
	}
}

void task3 (void) {
	while (1) {
		segment_set(3);
	}
}

void task4 (void) {
	while (1) {
		segment_set(4);
	}
}

void task5 (void) {
	while (1) {
		segment_set(5);
	}
}

void task6 (void) {
	while (1) {
		segment_set(6);
	}
}

void task7 (void) {
	while (1) {
		segment_set(7);
	}
}

void task8 (void) {
	while (1) {
		segment_set(8);
	}
}

void task9 (void) {
	while (1) {
		segment_set(9);
	}
}