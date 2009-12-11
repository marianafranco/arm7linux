/****************************************************************
 * IMPORT
 ****************************************************************/

#include "tasks.h"

extern int thread_array[];

int displayNumber;

/****************************************************************
 * ROUTINES
 ****************************************************************/


#define tasks_name_size 5


struct name_address tasks_name[] = {
	{"display_pid", &display_pid},
	{"set_segment", &set_segment},
	{"mutex_test", &mutex_test},
	{"fork_test", &fork_test},
	{"malicious_handler", &malicious_handler}
};


int strcmper (char* str1, char* str2){
	int i;
	for (i = 0; str1[i] == str2[i]; i++){
		if (str1[i] == '\0'){
			return 0;
		}
	}
	return str1[i] - str2[i];
}


pt2Task  get_task_addr(char* name){
	int i;
	for(i=0; i < tasks_name_size; i++){
		if(strcmper(tasks_name[i].name, name)==0){
			return tasks_name[i].task_ptr;
		}
	}
	return 0;
}



int get_state(int pid){
	if (pid > 9 || pid < 0){
		return 0;
	}else{
		return thread_array[pid];
	}
}


int get_task_name_size(){
	return tasks_name_size;
}

char* get_task_name(int index){
	return tasks_name[index].name;
}



/****************************************************************
 * TASKS
 ****************************************************************/



void set_segment(int value){
	while (1) {
		if (displayNumber != value) {
			segment_set(value);
			displayNumber = value;
		}
	}
}



void display_pid(int trash){
	while (1) {
		if (displayNumber != current_thread_id) {
			segment_set(current_thread_id);
			displayNumber = current_thread_id;
		}
	}
}



void fork_test(int trash){
	int a = 0;
	char pid[1];
	
	pid[0] = current_thread_id + 48;
	serial_print(COM0_USER, "\r\nparent = ");
	serial_print(COM0_USER, pid);
	serial_print(COM0_USER, ".\r\n");
	
	a = fork();
	if(a != -1 && a != 0){
		pid[0] = a + 48;
		serial_print(COM0_USER, "child = ");
		serial_print(COM0_USER, pid);
		serial_print(COM0_USER, ".\r\n");
		exit(a);
	}
	
	while(1){
		
	}
}



// Parte 1 do exemplo do mutex
void mutex_test (int led) {

	while (1) {
		int delay;
		/* Set display as 3 */
		if (displayNumber != current_thread_id) {
			segment_set(current_thread_id);
			displayNumber = current_thread_id;
		}
		/* Wait if mutex is on, if it is not, set it */
		WAIT;
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
		SIGNAL;
		/* Wait */
		for (delay=0; delay<0xffff; delay++) {} 
	}
}

void malicious_handler (int trash) {
	LED_1_OFF;
	LED_2_OFF;
	LED_3_OFF;
	LED_4_OFF;
	displayNumber = 0;
	install_handler ((unsigned)security_flaw, (unsigned *)IRQVector);
	while (1) {}
}

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