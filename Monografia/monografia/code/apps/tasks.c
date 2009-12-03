#include "tasks.h"


void task1 (void) {

	int a = 0;
	//char* newTask = "set_segment";
	
	int j;
	
	a = fork();
	if(a != -1 && a != 0){
	//	exec(a ,get_task_addr(newTask), 2);
	}
	
	while (1) {
		segment_set(1);
		if(j==1000000){
			exit(a);
		}
		j++;
	}
}

void task2 (int value) {
	while (1) {
		segment_set(2);		 
	}
}


void set_segment(int value){
	while (1) {
		segment_set(value);
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