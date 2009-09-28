#include "dips.h"

unsigned dips_read (void) 
{
	return SWITCH_MASK & *IOPDATA;
}
