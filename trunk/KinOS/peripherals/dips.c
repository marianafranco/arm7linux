#include "dips.h"

unsigned dips_read (void) 
{
	return 0xf & *IOData; // 0xf = SWITCH MASK
}
