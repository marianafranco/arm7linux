#include "debugger.h"

#include "segment.h"
#include "rpsarmul.h"


void task1 (void) {
	if(emulator == 1){
		while(1){
			cinit_print("Task1");
		}
	}else{
		while (1) {
			segment_set(1);
		}
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