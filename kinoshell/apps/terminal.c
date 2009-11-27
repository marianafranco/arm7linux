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

 #include <string.h>
 
/****************************************************************
 * MACROS
 ****************************************************************/

#define		angel_SWI	0x123456
#define	 	MAX_CMD_LENGTH	80


struct { char* name; void (*task_ptr)(int); } tasks_name[] = {
	{"task2", &task2},
	{"set_segment", &set_segment}
};


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


/*
int strcmp (char* str1, char* str2){
	int i;
	for (i = 0; str1[i] == str2[i]; i++){
		if (str1[i] == '\0'){
			return 0;
		}
	}
	return str1[i] - str2[i];
}
*/


pt2Task  get_task_addr(char* name){
	int i;
	for(i=0; i<sizeof(tasks_name); i++){
		if(strcmp(tasks_name[i].name, name)==0){
			return tasks_name[i].task_ptr;
		}
	}
	return 0;
}



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

void clearstring(char *str) {
	
	int i;
	
	for (i = 0; i < MAX_CMD_LENGTH; i++) {
		str[i] = 0;
	}
	
}

void getcommand(char *cmd) {
	
	int i, c;
	
	c=0; i=0;
	
	clearstring(cmd);
	
	while (c != '\r' && i < MAX_CMD_LENGTH) {
		c = serial_getchar();
		if (c == 8) {	// backspace
			if (i>0) {
			    serial_print(COM0_USER, " ");
			    i = i - 2;
			}
		}
		else {
			cmd[i++] = c;
		}
	}
}

void shell (void)
{
	char cmd[MAX_CMD_LENGTH];
	
	//int a = 0;
	//char* newTask = "set_segment";
	
	comm_init();
	
	serial_print(COM0_USER, "Bem-vindo!\r\n");
	while (1) {
	serial_print(COM0_USER, "\nDigite algo: ");
	
	getcommand(cmd);
	
	serial_print(COM0_USER, "\r\nVc digitou: ");
	serial_print(COM0_USER, cmd);
	serial_print(COM0_USER, "\r\n");
	}
		
	Exit();
}


/***************************************************************
 * END OF comm.c
 ***************************************************************/