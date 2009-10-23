#include "rpsarmul.h"

__swi(OS_SWI) void _syscall(int);
#define syscall(int) _syscall (int)

void irq_installSWIhandler (unsigned routine, unsigned *vector);
int fork (void);