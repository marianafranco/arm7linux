/* This file contains routines to initialize and handle DIPS interruptions */

#include "dips.h"

/* Return the value of the dip switches */
unsigned dips_read (void) 
{
	/* 0xf = switch mask */
	return 0XF & *IOData; 
}
