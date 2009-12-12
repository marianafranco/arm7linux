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
#define 	MAX_TASK_NAME	30

#define		ISALPHA(c) ((c >= 65 && c <= 90) || (c >= 97 && c <= 192))
#define		ISDIGIT(c) ((c >= 48 && c <= 57))


struct pid_name {char* pid; char name[MAX_TASK_NAME]; int state;} tasks[] = {
	{"1", "shell", 1},
	{"2", "", 0},
	{"3", "", 0},
	{"4", "", 0},
	{"5", "", 0},
	{"6", "", 0},
	{"7", "", 0},
	{"8", "", 0},
	{"9", "", 0}
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
	print ("\n** Welcome to KinOS!!");
  	print (" - Version 0.1 **\n\r");
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

void set_state(int pid, int state){
	tasks[pid-1].state = state;

}

void run_start(char *arg, int num) {
	int a = 0;
	int count = 0;
	int i;
	
	if (get_task_addr(arg) == 0){
		print("\nProgram not found.\r\n\n");
	
	}
		
		for(i=0; i< 9; i++){
			count = count + tasks[i].state;
		}
		
		if(count==9){
			print("\nImpossible to run more than 9 programs.\r\n\n");
			return;
		}
		
	else{
		
		a = fork();
		if(a != -1 && a != 0){
			print("\nProgram started.\r\n\n");
			exec(a ,get_task_addr(arg), num);
			memcpy(tasks[a - 1].name, arg, sizeof(char)*MAX_TASK_NAME);
			tasks[a - 1].state = 1;
		}
		
	}
	
}



void run_end(char *arg) {
	int i;
	
	// arg = all
	if(strcmper(arg, "all")==0){
		for(i=1; i < 9; i++){
			exit(i+1);
			tasks[i].state = 0;
		}
		print("\nFinished all programs.\r\n\n");
		
	// arg = task name
	}else{
		for(i=1; i < 9; i++){
			if(tasks[i].state == 1){
				if(strcmper(tasks[i].name, arg) == 0){
						exit(i+1);
						tasks[i].state = 0;
						print("\nProgram finished.\r\n\n");
						return;				
				}
			}
		}
		print("\nProgram not started.\r\n\n");
	}

}



void run_end_pid(int pid) {
	
	if(pid == 1){
		print("\nNot possible to kill the shell program.\r\n\n");
	}else if(pid<2 || pid > 9){
		print("\nIncorrect PID.\r\n\n");
	}else{
		exit(pid);
		tasks[pid - 1].state = 0;
		print("\nProgram finished.\r\n\n");
	}

}


void run_listtasks() {
	int i;
	print("\nTasks Name: \r\n\n");
	for(i=0; i<get_task_name_size(); i++){
		print(get_task_name(i));
		print("\r\n");
	}
	print("\r\n\n");
}



void run_ps() {

	int i;
	print("\nCurrently active threads:\r\n");
	print("\n");
	print("Name:\t\tPID:\r\n");
	// implementacao do ps vai aqui
	
	//run_start("task5", 0);
	
	for(i=0; i < 9; i++){
		if(tasks[i].state == 1){
			print(tasks[i].name);
			print("\t\t");
			print( tasks[i].pid);
			print("\r\n");		
		}
	}
	print("\r\n");
	
}




void run_help() {
	print("\nOther available commands for kinoshell:\r\n\n");
	print("                ps : Lists all currently active threads in KinOS\r\n");
	print("      start <name> : Starts a new thread with the program specified in <name>\r\n");
	print("start <name> <arg> : Starts a new thread with the program specified in <name>\r\n");
	print("                   : and the argument in <arg>\r\n");
	print("        end <name> : Kills the first threads named <name>\r\n");
	print("     end pid <num> : Kills the threads with the pid <num>\r\n");
	print("           end all : Kills all threads\r\n");
	print("             about : Displays additional information about the KinOS project\r\n");
	print("\n");
}



void run_about() {
	print("\nAbout KinOS v1.0 (December 2009)\r\n\n");
	print("Authors: Felipe Giunte Yoshida\r\n");
	print("         Mariana Ramos Franco\r\n");
	print("         Vinicius Tosta Ribeiro\r\n\n");
	print("Project advisor: Prof. Dr. Jorge Kinoshita\r\n\n");
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
	char *reservedwords[] = { "ps", "start", "end", "help", "about", "listtasks", "pid" };
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
				else if (ISALPHA(c) || c == '_') {
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
				else if (ISALPHA(c) || ISDIGIT(c) || c == '_') {
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
				else if (ISALPHA(c) || c == '_') {
					state = 3;
					word2[iw2] = c;
					iw2++;
				}
				else
					state = 666;
				break;
				
			case 3:
				if(ISALPHA(c) || ISDIGIT(c) || c == '_') {
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
				else if(ISDIGIT(c) || c=='a' || c=='b' || c=='c' || c=='d' || c=='e' || c=='f' ) {
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
			
		else if(strcmp(reservedwords[1], word1) == 0 && iw2 != 0 && word3[0] != 0){
			//numbers
			if(word3[0]>47 && word3[0]<58){
				run_start(word2, word3[0] - 48);
			// a, b, c, d, e, f
			}else if(word3[0]>96 && word3[0]<103){
				run_start(word2, word3[0] - 87);
			}
		}
		
		else if(strcmp(reservedwords[1], word1) == 0 && iw2 != 0 && word3[0] == 0)
			run_start(word2, 0);
			
		else if(strcmp(reservedwords[2], word1) == 0 && iw2 != 0 && word3[0] == 0)
			run_end(word2);
			
		else if(strcmp(reservedwords[2], word1) == 0 && strcmp(reservedwords[6], word2) == 0 && word3[0] != 0){
			//numbers
			if(word3[0]>49 && word3[0]<58){
				run_end_pid(word3[0] - 48);
			}else{
				print("\nThe pid must be a number between 2 and 9.\r\n\n");
			}
		}
			
		else if(strcmp(reservedwords[3], word1) == 0 && iw2 == 0 && word3[0] == 0)
			run_help();
			
		else if(strcmp(reservedwords[4], word1) == 0 && iw2 == 0 && word3[0] == 0)
			run_about();
			
		else if(strcmp(reservedwords[5], word1) == 0 && iw2 == 0 && word3[0] == 0)
			run_listtasks();
		
		else
			print("\nInvalid command.\r\n\n");
	}
	else {
		print("\nInvalid command.\r\n\n");
	}	

}



void printbanner() {

    print("Welcome to\r\n");
    print("------------------------------------------------------------\r\n");
    print("88      a8P   88                 ,ad8888ba,     ad88888ba   \r\n");
    print("88    ,88\'    \"\"                d8\"\'    `\"8b   d8\"     \"8b  \r\n");
    print("88  ,88\"                       d8\'        `8b  Y8,          \r\n");
    print("88,d88'       88  8b,dPPYba,   88          88  `Y8aaaaa,    \r\n");
    print("8888\"88,      88  88P\'   `\"8a  88          88    `\"\"\"\"\"8b,  \r\n");
    print("88P   Y8b     88  88       88  Y8,        ,8P          `8b  \r\n");
    print("88     \"88,   88  88       88   Y8a.    .a8P   Y8a     a8P  \r\n");
    print("88       Y8b  88  88       88    `\"Y8888Y\"\'     \"Y88888P\"   \r\n");
    print("------------------------------------------------------------\r\n\n");
    print("Type \'help\' for a list of available commands\r\n\n");

}
#include "../mutex/mutex.h"

void shell (void)
{
	char cmd[MAX_CMD_LENGTH];
	
	comm_init();
	printbanner();
	
	while (1) {
		
		WAIT;
		
		print("kinoshell> ");
		
		getcommand(cmd);
		
		parsecommand(cmd);
		
		SIGNAL;
		
		switch_thread();
		
	}
		
	Exit();
}


/***************************************************************
 * END OF comm.c
 ***************************************************************/