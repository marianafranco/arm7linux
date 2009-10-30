#include "rpsarmul.h"

typedef void (*pt2Task)(void);

__swi(OS_SWI) void syscall(int, int, pt2Task);

void irq_installSWIhandler (unsigned routine, unsigned *vector);
int fork (void);
void exec (int, pt2Task);
void exit (void);