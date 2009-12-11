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
#define	 	MAX_CMD_LENGTH	80
#define 	MAX_TASK_NAME	30

#define		ISALPHA(c) ((c >= 65 && c <= 90) || (c >= 97 && c <= 192))
#define		ISDIGIT(c) ((c >= 48 && c <= 57))


struct pid_name { int pid; char* name; int state;} tasks[] = {
	{1, "shell", 1},
	{2, "", 0},
	{3, "", 0},
	{4, "", 0},
	{5, "", 0},
	{6, "", 0},
	{7, "", 0},
	{8, "", 0},
	{9, "", 0}
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


void clearstring(char *str, int length) {
	
	int i;
	
	for (i = 0; i < length; i++) {
		str[i] = 0;
	}
	
}




void run_start(char *arg, int num) {
	int a = 0;
	
	a = fork();
	if(a != -1 && a != 0){
		exec(a ,get_task_addr(arg), 0);
		tasks[a - 1].name = arg;
		tasks[a - 1].state = 1;
	}
	
}




void run_end(char *arg) {

}


void run_listtasks() {
	serial_print(COM0_USER, "\nList Tasks command\r\n\n");
}



void run_ps() {

	int i;
	serial_print(COM0_USER, "\nCurrently active threads:\r\n");
	serial_print(COM0_USER, "\n");
	serial_print(COM0_USER, "Name:\t\tPID:\r\n");
	// implementacao do ps vai aqui
	
	run_start("task5", 0);
	
	for(i=0; i < 9; i++){
		if(tasks[i].state == 1){
			serial_print(COM0_USER, tasks[i].name);
			serial_print(COM0_USER, "\t\t");
			switch(tasks[i].pid){
				case 1:
					serial_print(COM0_USER,  "1");
					break;
				case 2:
					serial_print(COM0_USER,  "2");
					break;
				case 3:
					serial_print(COM0_USER,  "3");
					break;
				case 4:
					serial_print(COM0_USER,  "4");
					break;
				case 5:
					serial_print(COM0_USER,  "5");
					break;
				case 6:
					serial_print(COM0_USER,  "6");
					break;
				case 7:
					serial_print(COM0_USER,  "7");
					break;
				case 8:
					serial_print(COM0_USER,  "8");
					break;
				case 9:
					serial_print(COM0_USER,  "9");
					break;
			}
			serial_print(COM0_USER, "\r\n");		
		}
	}

	
}




void run_help() {
	serial_print(COM0_USER, "\nOther available commands for kinoshell:\r\n\n");
	serial_print(COM0_USER, "          ps : Lists all currently active threads in KinOS\r\n");
	serial_print(COM0_USER, "start <name> : Starts a new thread with the program specified in <name>\r\n");
	serial_print(COM0_USER, "  end <name> : Kills all threads named <name>\r\n");
	serial_print(COM0_USER, "       about : Displays additional information about the KinOS project\r\n");
	serial_print(COM0_USER, "\n");
}

void run_about() {
	serial_print(COM0_USER, "\nAbout KinOS v1.0 (December 2009)\r\n\n");
	serial_print(COM0_USER, "Authors: Felipe Giunte Yoshida\r\n");
	serial_print(COM0_USER, "         Mariana Ramos Franco\r\n");
	serial_print(COM0_USER, "         Vinicius Tosta Ribeiro\r\n\n");
	serial_print(COM0_USER, "Project advisor: Prof. Dr. Jorge Kinoshita\r\n\n");
}


/* -- getcommand -------------------------------------------------
 *
 * Reads a string from the COM0 port
 *
 */
void getcommand(char *cmd) {
	
	int i, c;
	
	c=0; i=0;
	
	clearstring(cmd, MAX_CMD_LENGTH);
	
	while (c != '\r' && i < MAX_CMD_LENGTH) {
		c = serial_getchar();
		if (c == 8) {	// backspace
			if (i>0) {
			    i--;
			}
		}
		else {
			cmd[i++] = c;
		}
	}
}

/* -- getcommand -------------------------------------------------
 *
 * Runs a finite state machine in order to parse user input (char *cmd)
 *
 */
void parsecommand(char *cmd) {

	int i, state, iw1, iw2, error;
	char c;
	char *reservedwords[] = { "ps", "start", "end", "help", "about", "listtasks" };
	char word1[MAX_CMD_LENGTH], word2[MAX_CMD_LENGTH], word3[2];
	
	error = 0;
	state = 0;
	iw1 = 0;
	iw2 = 0;
	
	clearstring(word1, MAX_CMD_LENGTH);
	clearstring(word2, MAX_CMD_LENGTH);
	clearstring(word3, 2);
	
	// sweeps the entire cmd string
	for (i = 0; i < MAX_CMD_LENGTH; i++) {
	
		c = cmd[i];
		
		switch (state) {
		
			case 0:
				if(c == ' ' || c == '\t')
					state = 0;
				else if (ISALPHA(c)) {
					state = 1;
					word1[iw1] = c;
					iw1++;
				}
				else
					state = 666;
				break;
			
			case 1:
				if(c == ' ' || c == '\t')
					state = 2;
				else if (c == '\r')
					state = 5;
				else if (ISALPHA(c) || ISDIGIT(c)) {
					state = 1;
					word1[iw1] = c;
					iw1++;
				}
				else
					state = 666;
				break;
			
			case 2:
				if(c == ' ' || c == '\t')
					state = 2;
				else if (c == '\r')
					state = 5;
				else if (ISALPHA(c)) {
					state = 3;
					word2[iw2] = c;
					iw2++;
				}
				else
					state = 666;
				break;
				
			case 3:
				if(ISALPHA(c) || ISDIGIT(c)) {
					state = 3;
					word2[iw2] = c;
					iw2++;
				}
				else if(c == ' ' || c == '\t')
					state = 4;
				else if(c == '\r')
					state = 5;
				else
					state = 666;
				break;
				
			case 4:
				if(c == ' ' || c == '\t')
					state = 4;
				else if(c == '\r')
					state = 5;
				else if(ISDIGIT(c)) {
					state = 6;
					word3[0] = c;
				}
				else
					state = 666;
				break;
			
			case 5:
				state = 5;
				break;
				
			case 6:
				if(c == ' ' || c == '\t')
					state = 6;
				else if(c == '\r')
					state = 5;
				else
					state = 666;
				break;
			
			case 666:
				//error = 1;
				break;
		}
		
		
	}
	
	if(state == 5) {
		// checks if word1 is one of the reserved words
		// and if the command's syntax is respected
		if(strcmp(reservedwords[0], word1) == 0 && iw2 == 0 && word3[0] == 0)
			run_ps();
			
		else if(strcmp(reservedwords[1], word1) == 0 && iw2 != 0 && word3[0] != 0)
			run_start(word2, word3[0] - 48);
			
		else if(strcmp(reservedwords[2], word1) == 0 && iw2 != 0 && word3[0] == 0)
			run_end(word2);
			
		else if(strcmp(reservedwords[3], word1) == 0 && iw2 == 0 && word3[0] == 0)
			run_help();
			
		else if(strcmp(reservedwords[4], word1) == 0 && iw2 == 0 && word3[0] == 0)
			run_about();
			
		else if(strcmp(reservedwords[5], word1) == 0 && iw2 == 0 && word3[0] == 0)
			run_listtasks();
		
		else
			serial_print(COM0_USER, "\nInvalid command.\r\n\n");
	}
	else {
		serial_print(COM0_USER, "\nInvalid command.\r\n\n");
	}	

}



void printbanner() {

    serial_print(COM0_USER, "Welcome to\r\n");
    serial_print(COM0_USER, "------------------------------------------------------------\r\n");
    serial_print(COM0_USER, "88      a8P   88                 ,ad8888ba,     ad88888ba   \r\n");
    serial_print(COM0_USER, "88    ,88\'    \"\"                d8\"\'    `\"8b   d8\"     \"8b  \r\n");
    serial_print(COM0_USER, "88  ,88\"                       d8\'        `8b  Y8,          \r\n");
    serial_print(COM0_USER, "88,d88'       88  8b,dPPYba,   88          88  `Y8aaaaa,    \r\n");
    serial_print(COM0_USER, "8888\"88,      88  88P\'   `\"8a  88          88    `\"\"\"\"\"8b,  \r\n");
    serial_print(COM0_USER, "88P   Y8b     88  88       88  Y8,        ,8P          `8b  \r\n");
    serial_print(COM0_USER, "88     \"88,   88  88       88   Y8a.    .a8P   Y8a     a8P  \r\n");
    serial_print(COM0_USER, "88       Y8b  88  88       88    `\"Y8888Y\"\'     \"Y88888P\"   \r\n");
    serial_print(COM0_USER, "------------------------------------------------------------\r\n\n");
    serial_print(COM0_USER, "Type \'help\' for a list of available commands\r\n\n");

}


void shell (void)
{
	char cmd[MAX_CMD_LENGTH];
	
	comm_init();
	printbanner();
	
	while (1) {
		serial_print(COM0_USER, "kinoshell> ");
		
		getcommand(cmd);
		
		parsecommand(cmd);
		
	}
		
	Exit();
}


/***************************************************************
 * END OF comm.c
 ***************************************************************/