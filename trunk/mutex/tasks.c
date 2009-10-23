#include "tasks.h"

int a = 1;

void task1 (void) {
	while (1) {
		segment_set(1);
		if (a == 1) {
			a = fork();
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