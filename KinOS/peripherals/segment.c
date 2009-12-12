/************************************************************************************
	KinOS - Microkernel for ARM Evaluator 7-T
	Seniors project - Computer Engineering
	Escola Politecnica da USP, 2009
	
	Felipe Giunte Yoshida
	Mariana Ramos Franco
	Vinicius Tosta Ribeiro
*/

/* 
	The program was based on the mutex program by ARM - Strategic Support Group,
	contained on the ARM Evaluator 7-T example CD, under the folder /Evaluator7-T/
	source/examples/mutex/ 
*************************************************************************************/


/* This file contains routines to initialize and handle the 7 segment display */

#include "segment.h"

/* Calculates the proper display addresses value according to the number */
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

/* Set number on the display */
void segment_set (int seg) {
	if ( seg >= 0 & seg <= 0xf ) {
		*IOData 	&= ~Segment_mask;
		*IOData 	|= numeric_display[seg];
	}
}

/* Initialize 7-segment display */
void segment_init (void) {
	*IOPMod |= Segment_mask;
	*IOData |= Segment_mask;
}