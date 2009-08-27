#include "cinit.h"

int IntCT1;

void task1 (void) {
	int delay;
	while (1) {
		// Dummy time delay
		cinit_print ("Process 1\n");
		for (delay=0; delay<0x40ffff; delay++) {}
		  
	}
}

void task2 (void) {
int delay;
	while (1) {
		// Dummy time delay
		cinit_print ("Process 2\n"); 
		for (delay=0; delay<0x40ffff; delay++) {}
		 
	}
}

void task3 (void) {
int delay;
	while (1) {
		cinit_print ("Process 3\n");  
		// Dummy time delay
		for (delay=0; delay<0x40ffff; delay++) {}
	}
}

void task4 (void) {
int delay;
	while (1) {
		cinit_print ("Process 4\n");  
		// Dummy time delay
		for (delay=0; delay<0x40ffff; delay++) {}
	}
}

void task5 (void) {
int delay;
	while (1) {
		cinit_print ("Process 5\n");
		// Dummy time delay
		for (delay=0; delay<0x40ffff; delay++) {}  
	}
}

void task6 (void) {
int delay;
	while (1) {
		cinit_print ("Process 6\n");
		// Dummy time delay
		for (delay=0; delay<0x40ffff; delay++) {}  
	}
}

void task7 (void) {
int delay;
	while (1) {
		cinit_print ("Process 7\n"); 
		// Dummy time delay
		for (delay=0; delay<0x40ffff; delay++) {}
	}
}

void task8 (void) {
int delay;
	while (1) {
		cinit_print ("Process 8\n");  
		// Dummy time delay
		for (delay=0; delay<0x40ffff; delay++) {}
	}
}

void task9 (void) {
int delay;
	while (1) {
		cinit_print ("Process 9\n");  
		// Dummy time delay
		for (delay=0; delay<0x40ffff; delay++) {}
	}
}