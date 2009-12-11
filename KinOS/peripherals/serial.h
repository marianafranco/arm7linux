/*************************************************************
 *
 *	ARM Strategic Support Group
 *
 *************************************************************/

/*************************************************************
 *
 *	Module		: serial.h
 *	Description	: simple code to drive the serial port on the
 *				  Evaluator7T.
 * 	Tool Chain	: ARM Developer Suite 1.0
 * 	Platform	: Evaluator7T
 * 	History		:
 *
 *		2000-3-29 Andrew N. Sloss
 *		- started serial module
 *
 **************************************************************/
 
/**************************************************************
 * IMPORT
 **************************************************************/
 
// none...

/**************************************************************
 * MACROS
 **************************************************************/

#define BAUD_9600	   	(162 << 4)

#define COM1_DEBUG		(1)
#define COM0_USER		(0)

/**************************************************************
 * DATATYPES
 **************************************************************/

// none...

/**************************************************************
 * STATICS
 **************************************************************/

// none...

/**************************************************************
 * ROUTINES
 **************************************************************/

/* -- serial_initcom0user --------------------------------------
 *
 * Description	: initializes the USER/COM0 serial port.
 *
 * Parameters	: unsigned baudrate - baudrate i.e. 9600
 * Return		: none...
 * Notes		: none...
 *
 */

void serial_initcom0user (unsigned baudrate);

/* -- serial_initcom1debug -------------------------------------
 *
 * Description	: initializes the DEBUG/COM1 serial port.
 *
 * Parameters	: unsigned baudrate - baudrate i.e. 9600
 * Return		: none...
 * Notes		: none...
 *
 */
 
void serial_initcom1debug (unsigned baudrate);

/* -- serial_print ---------------------------------------------
 *
 * Description	: print out a string through the com port
 *
 * Parameters	: unsigned port - USER/DEBUG
 * 				: char *s - string to be printed out.
 * Return		: none...
 * Notes		: none...
 *
 */

void serial_print (unsigned port, char *s);		
	
/* -- serial_getkey --------------------------------------------
 *
 * Description	: standard implementation of getkey.
 *
 * Parameters	: none...
 * Return		: none...
 * Notes		: 
 *
 *			waits until a key is pressed then echo's back.
 *
 */	
	
void serial_getkey (void);	


char serial_getchar(void);

void serial_irq(void);
		
/*****************************************************************
 * END OF serial.h 
 *****************************************************************/