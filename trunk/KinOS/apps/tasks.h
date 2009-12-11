#include "../peripherals/segment.h"
#include "../interrupt/swi.h"
#include "../mutex/mutex.h"
#include "../peripherals/led.h"


void display_pid(int);
void mutex_test (int);
void set_segment(int);

extern int current_thread_id;

int strcmper (char* str1, char* str2);
pt2Task  get_task_addr(char* name);
int get_state(int pid);
int get_task_name_size(void);
char* get_task_name(int index);


struct name_address { 
	char* name; 			// The task name
	void (*task_ptr)(int); 	// Pointer to the task
}; 
