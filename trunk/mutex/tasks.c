#include "segment.h"


// LED STUFF

// -- Samsung KS32C50100 settings ....

#define SYSCFG			0x03ff0000
#define IOPMOD          ((volatile unsigned *)(SYSCFG+0x5000))
#define IOPDATA         ((volatile unsigned *)(SYSCFG+0x5008))

static unsigned int numeric_display [16] = 
{
	DISP_0,
	DISP_1,
	DISP_2,
	DISP_3,
	DISP_4,
	DISP_5,
	DISP_6,
	DISP_7,
	DISP_8,
	DISP_9,
	DISP_A,
	DISP_B,
	DISP_C,
	DISP_D,
	DISP_E,
	DISP_F
};


void segment_setdisplay (unsigned d)
{
		*IOPDATA 	&= ~SEG_MASK;
		*IOPDATA 	|= d;	
}

void segment_set (int seg)
{
	if ( seg >= 0 & seg <= 0xf ) 
		segment_setdisplay(numeric_display[seg]);

}

void segment_init (void)
{
	*IOPMOD 	|= SEG_MASK;
	*IOPDATA 	|= SEG_MASK;
}




int IntCT1;

void task1 (void) {
	int delay;
	while (1) {
		// Dummy time delay
		//cinit_print ("Process 1\n");
		segment_set(1);
		for (delay=0; delay<0x40ffff; delay++) {}
		  
	}
}

void task2 (void) {
int delay;
	while (1) {
		// Dummy time delay
		//cinit_print ("Process 2\n"); 
		segment_set(2);
		for (delay=0; delay<0x40ffff; delay++) {}
		 
	}
}

void task3 (void) {
int delay;
	while (1) {
		//cinit_print ("Process 3\n");  
		// Dummy time delay
		segment_set(3);
		for (delay=0; delay<0x40ffff; delay++) {}
	}
}

void task4 (void) {
int delay;
	while (1) {
		//cinit_print ("Process 4\n");  
		// Dummy time delay
		segment_set(4);
		for (delay=0; delay<0x40ffff; delay++) {}
	}
}

void task5 (void) {
int delay;
	while (1) {
		//cinit_print ("Process 5\n");
		// Dummy time delay
		segment_set(5);
		for (delay=0; delay<0x40ffff; delay++) {}  
	}
}

void task6 (void) {
int delay;
	while (1) {
		//cinit_print ("Process 6\n");
		// Dummy time delay
		segment_set(6);
		for (delay=0; delay<0x40ffff; delay++) {}  
	}
}

void task7 (void) {
int delay;
	while (1) {
		//cinit_print ("Process 7\n"); 
		// Dummy time delay
		segment_set(7);
		for (delay=0; delay<0x40ffff; delay++) {}
	}
}

void task8 (void) {
int delay;
	while (1) {
		//cinit_print ("Process 8\n");  
		// Dummy time delay
		segment_set(8);
		for (delay=0; delay<0x40ffff; delay++) {}
	}
}

void task9 (void) {
int delay;
	while (1) {
		//cinit_print ("Process 9\n");  
		// Dummy time delay
		segment_set(9);
		for (delay=0; delay<0x40ffff; delay++) {}
	}
}