#include "rpsarmul.h"

void irq_installSWIhandler (unsigned routine, unsigned *vector);

extern int  Angel_SWI_Address;

/***** MARI *********/

typedef void (*pt2Task)(void);

extern void rotina_exec(int, pt2Task);
/***** END MARI *****/


__swi(fork_SWI) void _fork(int);
//__swi(exec_SWI) void _exec(int);
__swi(exec_SWI) void _exec(int, pt2Task);
__swi(exit_SWI) void _exit(int);

#define fork(process) _fork (process)

/***** MARI *********/
#define exec(process, proc_addr) _exec (process, proc_addr)
//#define exec(process) _exec (process)
/***** END MARI *****/

#define exit(process) _exit (process)
