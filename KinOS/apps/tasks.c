#include "tasks.h"


struct name_address tasks_name[] = {
	{"task2", &task2},
	{"task3", &task3},
	{"task4", &task4},
	{"set_segment", &set_segment}
};


int strcmp (char* str1, char* str2){
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
	for(i=0; i<sizeof(tasks_name); i++){
		if(strcmp(tasks_name[i].name, name)==0){
			return tasks_name[i].task_ptr;
		}
	}
	return 0;
}




void task1 (void) {

	int a = 0;
	int b = 0;
	char* newTask = "set_segment";
	
	int j;
	
	a = fork();
	if(a != -1 && a != 0){
		exec(a ,get_task_addr("task3"), 0);
	}
	
	b = fork();
	if(b != -1 && b != 0){
		exec(b ,get_task_addr("task4"), 0);
	}
	
	while (1) {
		segment_set(1);
		/*if(j==1000000){
			exit(a);
		}
		j++;*/
	}
}

void task2 (int value) {
	while (1) {
		segment_set(2);		 
	}
}


void set_segment(int value){
	while (1) {
		segment_set(value);
	}
}




// Parte 1 do exemplo do mutex
void task3 (int lixo) {

	while (1) {
		int delay;
		/* Set display as 3 */
		segment_set(3);
		/* Wait if mutex is on, if it is not, set it */
		//WAIT;
		/* Turn on LED 1 */
		//LED_1_ON;
		/* Wait */
		//for (delay=0; delay<0x20ffff; delay++) {}
		/* Turn off LED 1 */
		//LED_1_OFF;
		/* Turn mutex off */ 
		//SIGNAL;
		/* Wait */
		//for (delay=0; delay<0x20ffff; delay++) {} 
	}
}

// Parte 2 do exemplo do mutex
void task4 (int lixo) {
	while (1) {
		int delay;
		/* Set display as 3 */
		segment_set(4);
		/* Wait if mutex is on, if it is not, set it */
		//WAIT;
		/* Turn on LED 1 */
		//LED_2_ON;
		/* Turn mutex off */ 
		//SIGNAL;
		/* Turn off LED 1 */
		//LED_2_OFF;
		/* Wait */
		//for (delay=0; delay<0x20ffff; delay++) {}
		/* Wait */
		//for (delay=0; delay<0x20ffff; delay++) {} 
	}
}

void task5 (void) {
	while (1) {
		segment_set(5);
	}
}

void task6 (void) {
	while (1) {
		segment_set(6);
	}
}

void task7 (void) {
	while (1) {
		segment_set(7);
	}
}

void task8 (void) {
	while (1) {
		segment_set(8);
	}
}

void task9 (void) {
	while (1) {
		segment_set(9);
	}
}