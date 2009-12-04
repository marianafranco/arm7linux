/****************************************************************
 *
 * ARM Strategic Support Group
 * 
 ****************************************************************/

/****************************************************************
 *
 *	Module		: comm.c
 *	Description	: communicates with the serial driver.
 *  Tool Chain	: ARM Developer Suite 1.0
 *	Platform	: Evaluator7T
 * 	History		: 
 *
 *					2000-03-22 Andrew N. Sloss
 *					- implemented
 *				
 *
 ****************************************************************/

/****************************************************************
 * IMPORT
 ****************************************************************/

 #include "serial.h"
 #include "tasks.h"
 
/****************************************************************
 * MACROS
 ****************************************************************/

#define		angel_SWI	0x123456
#define	 	CMD_LENGTH	32


/****************************************************************
 * MISC
 ****************************************************************/

__swi (angel_SWI) void _Exit(unsigned op, unsigned except);
#define Exit() _Exit(0x18,0x20026) 

__swi (angel_SWI) void _WriteC(unsigned op, const char *c);
#define WriteC(c) _WriteC (0x3,c)


/****************************************************************
 * ROUTINES
 ****************************************************************/



/* -- comm_print ------------------------------------------------
 *
 * Description	: write a string via the Angel SWI call WriteC
 *
 * Parameters	: const char *string - string to be written
 * Return		: none...
 * Notes		: none...
 *
 */

void comm_print (const char *string)
{ 
	int pos = 0;
	while (string[pos] != 0) WriteC(&string[pos++]);
}

/* -- comm_init -------------------------------------------------
 *
 * Description	: initialize the COM0 port and set to 9600 baud.
 *
 * Parameters	: none...
 * Return		: none...
 * Notes		: none...
 *
 */
 
void comm_init (void)
{ 
	serial_initcom0user (BAUD_9600); 
}	

/* -- comm_banner -----------------------------------------------
 *
 * Description	: print out standard banner out of the COM0 port
 *
 * Parameters	: none...
 * Return		: none...
 * Notes		: none...
 *
 */

void comm_banner (void) 
{ 
	serial_print (COM0_USER, "\n** Welcome to KinOS!!");
  	serial_print (COM0_USER, " - Version 0.1 **\n\r");
}

/* -- comm_getkey -----------------------------------------------
 *
 * Description	: wait until a key is press from the host PC.
 *
 * Parameters	: none...
 * Return		: none...
 * Notes		: none...
 *
 */

void comm_getkey (void)
{ 
	serial_getkey(); 
}


char comm_getcmd (void)
{ 
	return serial_getcmd(); 
}


/* -- C_Entry --------------------------------------------------
 *
 * Description	: Entry point into C
 *
 * Parameters	: none...
 * Return		: none...
 * Notes		: none...
 *
 */

void shell (void)
{
	char cmd[CMD_LENGTH];
	char c;
	int i;
	
	//int a = 0;
	//char* newTask = "set_segment";
	
	comm_print ("\n-- switch to a serial terminal program (baud=9600)\n" );
		 
	comm_init();
	comm_banner();
	
	// wait for a key press...

	serial_print (COM0_USER,"-- Press any key \n\r");
	
	
	c=0;
	i=0;
	while (c != '\r' && i<CMD_LENGTH) {
		c = comm_getcmd();
		if (c == 8) {	// backspace
			if (i>0) i--;
		} else {
			cmd[i++] = c;
		}
	} 
	
	
	
	//a = fork();
	//if(a != -1 && a != 0){
	//	exec(a ,get_task_addr(newTask), 1);
	//}
	
	//while(1){
		segment_set(1);
	//}
	
	comm_getkey();
	serial_print (COM0_USER,"\n\r-- Key pressed \n\r");
	serial_print (COM0_USER,"\n\r** Program Terminating **\n\r");
	
	comm_print ("\n\n ** program terminating normally **");	
		
	Exit();
}


/***************************************************************
 * END OF comm.c
 ***************************************************************/