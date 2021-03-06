/***************************************************************
	KinOS - Microkernel for ARM Evaluator 7-T
	Seniors project - Computer Engineering
	Escola Politecnica da USP, 2009
	
	Felipe Giunte Yoshida
	Mariana Ramos Franco
	Vinicius Tosta Ribeiro
*/

/* 
	The program was based on the mutex program by ARM - Strategic Support Group,
	contained on the ARM Evaluator 7-T example CD, under the folder /Evaluator7-T/
	source/examples/mutex/ 
*****************************************************************/

/****************************************************************
 * IMPORT
 ****************************************************************/

#include "tasks.h"
#include "terminal.h"


/****************************************************************
 * EXTERN
 ****************************************************************/

extern int thread_array[];


/****************************************************************
 * GLOBAL VARIABLES
 ****************************************************************/

// The number which is showed in the display
int displayNumber;

// Struct which saves the task name and task address
struct name_address tasks_name[] = {
	{"display_pid", &display_pid},
	{"set_led", &set_led},
	{"set_segment", &set_segment},
	{"mutex_test", &mutex_test},
	{"fork_test", &fork_test},
	{"dips_to_leds", &dips_to_leds},
	{"dips_to_segments", &dips_to_segments},
	{"malicious_handler", &malicious_handler},
	{"tictactoe", &play_tictactoe}
};

/****************************************************************
 * MACRO
 ****************************************************************/

// The number of tasks in the struct tasks_name
#define tasks_name_size 9


/****************************************************************
 * ROUTINES
 ****************************************************************/

// Compare two strings
int strcmper (char* str1, char* str2){
	int i;
	for (i = 0; str1[i] == str2[i]; i++){
		if (str1[i] == '\0'){
			return 0;
		}
	}
	return str1[i] - str2[i];
}

// Get the task address
pt2Task  get_task_addr(char* name){
	int i;
	for(i=0; i < tasks_name_size; i++){
		if(strcmper(tasks_name[i].name, name)==0){
			return tasks_name[i].task_ptr;
		}
	}
	return 0;
}

// Get the thread state (active/inactive) 
int get_state(int pid){
	if (pid > 9 || pid < 0){
		return 0;
	}else{
		return thread_array[pid];
	}
}

// Get the size of the struct task_name
int get_task_name_size(){
	return tasks_name_size;
}

// Get the task name from the struct task_name
char* get_task_name(int index){
	return tasks_name[index].name;
}


/****************************************************************
 * TASKS
 ****************************************************************/


// Show in the LEDs the value passed as argument
void set_led(int value){
	switch (value) {
		case 0:
			LED_1_OFF;
			LED_2_OFF;
			LED_3_OFF;
			LED_4_OFF;
			break;
		case 1:
			LED_1_OFF;
			LED_2_OFF;
			LED_3_OFF;
			LED_4_ON;
			break;
		case 2:
			LED_1_OFF;
			LED_2_OFF;
			LED_3_ON;
			LED_4_OFF;
			break;
		case 3:
			LED_1_OFF;
			LED_2_OFF;
			LED_3_ON;
			LED_4_ON;
			break;
		case 4:
			LED_1_OFF;
			LED_2_ON;
			LED_3_OFF;
			LED_4_OFF;
			break;
		case 5:
			LED_1_OFF;
			LED_2_ON;
			LED_3_OFF;
			LED_4_ON;
			break;
		case 6:
			LED_1_OFF;
			LED_2_ON;
			LED_3_ON;
			LED_4_OFF;
			break;
		case 7:
			LED_1_OFF;
			LED_2_ON;
			LED_3_ON;
			LED_4_ON;
			break;
		case 8:
			LED_1_ON;
			LED_2_OFF;
			LED_3_OFF;
			LED_4_OFF;
			break;
		case 9:
			LED_1_ON;
			LED_2_OFF;
			LED_3_OFF;
			LED_4_ON;
			break;
		case 10:
			LED_1_ON;
			LED_2_OFF;
			LED_3_ON;
			LED_4_OFF;
			break;
		case 11:
			LED_1_ON;
			LED_2_OFF;
			LED_3_ON;
			LED_4_ON;
			break;
		case 12:
			LED_1_ON;
			LED_2_ON;
			LED_3_OFF;
			LED_4_OFF;
			break;
		case 13:
			LED_1_ON;
			LED_2_ON;
			LED_3_OFF;
			LED_4_ON;
			break;
		case 14:
			LED_1_ON;
			LED_2_ON;
			LED_3_ON;
			LED_4_OFF;
			break;
		case 15:
			LED_1_ON;
			LED_2_ON;
			LED_3_ON;
			LED_4_ON;
			break;		
		}
		set_state(current_thread_id, 0);
		exit(current_thread_id);
		while(1);
}


// Set in the display the value passed as argument
void set_segment(int value){
	while (1) {
		if (displayNumber != value) {
			segment_set(value);
			displayNumber = value;
		}
	}
}


// Set in the display the thread's pid
void display_pid(int trash){
	while (1) {
		if (displayNumber != current_thread_id) {
			segment_set(current_thread_id);
			displayNumber = current_thread_id;
		}
	}
}


// The tictactoe program
void play_tictactoe(int trash) {
	
	WAIT_SHELL;
	tictactoe();
	SIGNAL_SHELL;
	
	set_state(current_thread_id, 0);
	exit(current_thread_id);
	while(1){}
}


// Exemple of fork/exec
void fork_test(int trash){
	int a = 0;
	char pid[1];
	
	pid[0] = current_thread_id + 48;
	print("\r\nparent = ");
	print(pid);
	print(".\r\n");
	
	a = fork();
	if(a != -1 && a != 0){
		pid[0] = a + 48;
		print("child = ");
		print(pid);
		print(".\r\n");
		exit(a);
	}
	
	while(1){
		
	}
}


// Example of mutex
void mutex_test (int led) {

	if (led >= 1 && led <= 4) {
	
		while (1) {
			int delay;
			/* Set display as 3 */
			if (displayNumber != current_thread_id) {
				segment_set(current_thread_id);
				displayNumber = current_thread_id;
			}
			/* Wait if mutex is on, if it is not, set it */
			WAIT_EXAMPLE;
			/* Turn on LED 1 */
			switch (led) {
				case 1:
					LED_1_ON;
					break;
				case 2:
					LED_2_ON;
					break;
				case 3:
					LED_3_ON;
					break;
				case 4:
					LED_4_ON;
					break;
			}
			
			/* Wait 20ffff*/
			for (delay=0; delay<0xffff; delay++) {}
			/* Turn off LED 1 */
			switch (led) {
				case 1:
					LED_1_OFF;
					break;
				case 2:
					LED_2_OFF;
					break;
				case 3:
					LED_3_OFF;
					break;
				case 4:
					LED_4_OFF;
					break;
			}
			/* Turn mutex off */ 
			SIGNAL_EXAMPLE;
			/* Wait */
			for (delay=0; delay<0xffff; delay++) {} 
		}
	}
	else {
		// kills the process if it received invalid parameters
		print("Invalid parameter for mutex_test\r\n\n");
		
		set_state(current_thread_id, 0);
		exit(current_thread_id);
		while(1){}
	}
}


// Malicious program wich install a handler 
// Atention!! This program will lock the system
void malicious_handler (int trash) {
	LED_1_OFF;
	LED_2_OFF;
	LED_3_OFF;
	LED_4_OFF;
	displayNumber = 0;
	install_handler ((unsigned)security_flaw, (unsigned *)IRQVector);
	while (1) {}
}


// Routine used in the malicious_handler
void security_flaw (int trash) {
	int delay;
	while (1) {
		switch (displayNumber) {
		case 0:
			LED_1_ON;
			LED_2_ON;
			LED_3_ON;
			LED_4_ON;
			displayNumber = 15;
			break;
		case 15:
			LED_1_OFF;
			LED_2_OFF;
			LED_3_OFF;
			LED_4_OFF;
			displayNumber = 0;
			break;
		}
		for (delay = 0; delay <= 0x001ffff0; delay++) {};
	}	
} 


// Set in the LEDs the value give in the switches
void dips_to_leds (int trash) {
	set_led(dips_read());
}


// Set in the display the value give in the switches
void dips_to_segments (int trash) {
	
	int setvalue;
	
	setvalue = (int)(dips_read());
	segment_set(setvalue);
	print("DIP value succesfully setted on the display!\r\n\n");
	
	set_state(current_thread_id, 0);
	exit(current_thread_id);
	while(1){}
}
