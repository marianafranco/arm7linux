#include "constants.h"

typedef void (*pt2Task)(void);

__swi(OS_SWI) int syscall(int, int, pt2Task);

int fork (void);
void exec (int, pt2Task);
void exit (int);