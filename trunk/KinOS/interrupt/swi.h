/****************************************************************
 * IMPORT
 ****************************************************************/

#include "constants.h"


/****************************************************************
 * TYPEDEF
 ****************************************************************/

typedef void (*pt2Task)(int);


/****************************************************************
 * MISC
 ****************************************************************/
 
/* SWI routine syscall */ 
__swi(OS_SWI) int syscall(int, int, pt2Task, int);


/* SWI routine syscall_print */ 
__swi(OS_SWI) int syscall_print(int, int, char*, int);


/****************************************************************
 * ROUTINES
 ****************************************************************/
 
/* Calls the fork system call and return the child id or zero */ 
int fork (void);

/* Calls the exec system call */
void exec (int, pt2Task, int);

/* Calls the exit system call */
void exit (int);

/* Calls the print system call */
void print(char *str);

/* Calls the switch_thread system call */
void switch_thread (void);