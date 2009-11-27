/*****************************************************************
 *
 * ARM - Strategic Support Group
 *
 *****************************************************************/

/*****************************************************************
 *
 * Module		: Mutex
 * Description  : Simple Mutual Exclusion module that allows 
 * 		  		  critical sections of code to have access to 
 *		  		  shared memory.
 * Tool chain 	: ARM Developers Suite 1.0
 * Platform		: Evalutator7T
 * History		:
 *		
 *		990930 ASloss
 *		- designed simple mutex program
 *
 *		991117 ASloss
 *		- added spin lock
 *
 *		2000-03-25 Andrew N. Sloss
 *		- ported to Evaluator7T
 *
 * Notes 	: none...
 *
 ******************************************************************/

/******************************************************************
 * IMPORT
 ******************************************************************/

// none...

/******************************************************************
 * MACROS
 ******************************************************************/

// none...

/******************************************************************
 * STATICS
 ******************************************************************/

unsigned volatile int semaphore	= 2; // this is a start value

/******************************************************************
 * ROUTINES
 ******************************************************************/


/* -- mutex_gatelock ----------------------------------------------
 *
 * Description 	: Locks the semaphore... 
 * 
 * Parameters	: none...
 * Return		: none...
 * Notes		:
 *
 */
	
void mutex_gatelock (void) 
{
	__asm 
	{
	spin:
	mov		r1, &semaphore
	mov		r2, #1
	swp		r3,r2,[r1]
	cmp		r3,#1
	beq		spin
	}
}

/* -- mutex_gateunlock -------------------------------------------
 *
 * Description 	: Unlocks the semaphore ...
 * 
 * Parameters	: none...
 * Return		: none...
 * Notes		:
 *
 */

void mutex_gateunlock (void) 
{

	__asm 
	{
	mov		r1, &semaphore
	mov		r2, #0
	swp		r0,r2,[r1]
	}


}

/*****************************************************************
 * END OF mutex.c
 *****************************************************************/

