/**************************************************************
 *
 * ARM - Strategic Support Group
 *
 **************************************************************/

/**************************************************************
 * IMPORT
 **************************************************************/

// none...

/***************************************************************
 *
 * Module		: mutex.h
 * Description  : 
 *
 *		Simple Mutual Exclusion module that allows 
 * 		critical sections of code to have access to 
 *		shared memory.
 *
 * Tool Chain	: ARM Developer Suite v1.0
 * Platform		: Evaluator7T
 * History	:
 *		
 *		993009 ASloss
 *		- designed simple mutex program
 *
 *		2000-04-02 Andrew N. Sloss
 *		- ported to the Evaluator7T
 *
 * Notes 	: none...
 *
 ****************************************************************/

/****************************************************************
 * MACROS
 ****************************************************************/

#define aWAIT 		while (semaphore==1) {} mutex_gatelock(); 
#define aSIGNAL 	mutex_gateunlock(); 	

#define bWAIT 		while (semaphore==1||semaphore==2) {} 	\
					mutex_gatelock();  

#define bSIGNAL 	mutex_gateunlock(); 

/****************************************************************
 * EXTERNAL
 ****************************************************************/

extern unsigned volatile int semaphore; // do not access directly

/* -- mutex_gatelock ----------------------------------------------
 *
 * Description 	: Locks the semaphore... 
 * 
 * Parameters	: none...
 * Return	: none...
 * Notes	:
 *
 */

void mutex_gatelock (void);

/* -- mutex_gateunlock --------------------------------------------
 *
 * Description 	: Unlocks the semaphore ...
 * 
 * Parameters	: none...
 * Return	: none...
 * Notes	:
 *
 */

void mutex_gateunlock (void);

/******************************************************************
 * END OF mutex.h
 ******************************************************************/