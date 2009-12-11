#include "constants.h"

typedef void (*pt2Task)(int);

__swi(OS_SWI) int syscall(int, int, pt2Task, int);

__swi(OS_SWI) int syscall_print(int, int, char*, int);

int fork (void);
void exec (int, pt2Task, int);
void exit (int);

void print(char *str);