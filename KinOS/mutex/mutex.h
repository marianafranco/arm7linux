/**************************************************************
 * EXTERNAL
 **************************************************************/
 
extern unsigned volatile int semaphore; // do not access directly


/**************************************************************
 * MACROS
 **************************************************************/

#define WAIT 		while (semaphore==1) {} mutex_gatelock(); 
#define SIGNAL 		mutex_gateunlock(); 	


/****************************************************************
 * ROUTINES
 ****************************************************************/


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
