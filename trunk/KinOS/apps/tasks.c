/****************************************************************
 * IMPORT
 ****************************************************************/

#include "tasks.h"

extern int thread_array[];

int displayNumber;

/****************************************************************
 * ROUTINES
 ****************************************************************/


<<<<<<< .mine
#define tasks_name_size 4
=======
#define tasks_name_size 3
>>>>>>> .r166

struct name_address tasks_name[] = {
	{"display_pid", &display_pid},
	{"set_segment", &set_segment},
	{"mutex_test", &mutex_test},
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


/*void task1 (void) {

	int a = 0;
	int b = 0;
	int c = 0;
	
	char* newTask = "set_segment";
	
	int j;
	
	int state1;
	int state2;
	
	//j = getState(0) + getState(1) + getState(2);
	
	a = fork();
	if(a != -1 && a != 0){
		exec(a ,get_task_addr("task3"), 0);
	}
	
	b = fork();
	if(b != -1 && b != 0){
		exec(b ,get_task_addr("task4"), 0);
	}
	
	
	c = fork();
	if(c != -1 && b != 0){
		exec(c ,get_task_addr("task5"), 0);
	}
	
	
	while (1) {
		segment_set(1);
		if(j==1000000){
			exit(a);
		}
		j++;
	}
}*/


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
	displayNumber = 1;
	install_handler ((unsigned)security_flaw, (unsigned *)IRQVector);
	while (1) {}
}

void security_flaw (int trash) {
	
	switch (displayNumber) {
		case 1:
			LED_2_ON;
			LED_1_OFF;
			LED_3_OFF;
			LED_4_OFF;
			displayNumber = 2;
			break;
		case 2:
			LED_3_ON;
			LED_1_OFF;
			LED_2_OFF;
			LED_4_OFF;
			displayNumber = 3;
			break;
		case 3:
			LED_4_ON;
			LED_1_OFF;
			LED_2_OFF;
			LED_3_OFF;
			displayNumber = 4;
			break;
		case 4:
			LED_1_ON;
			LED_2_OFF;
			LED_3_OFF;
			LED_4_OFF;
			displayNumber = 1;
			break;
		}
	timer_irq();
	
	while (1) {}
} 