#include "segment.h"

static unsigned int numeric_display [16] =  {
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


void segment_setdisplay (unsigned d) {
		*IOPDATA 	&= ~SEG_MASK;
		*IOPDATA 	|= d;	
}

void segment_set (int seg) {
	if ( seg >= 0 & seg <= 0xf ) 
		segment_setdisplay(numeric_display[seg]);

}

// Initialize 7-segment display
void segment_init (void) {
	*IOPMOD 	|= SEG_MASK;
	*IOPDATA 	|= SEG_MASK;
}