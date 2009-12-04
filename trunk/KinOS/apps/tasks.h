#include "../peripherals/segment.h"
#include "../interrupt/swi.h"
#include "../mutex/mutex.h"
#include "../peripherals/led.h"

void task1 (void);
void task2 (int);
void task3 (int);
void task4 (int);
void set_segment(int);


int strcmp (char* str1, char* str2);
pt2Task  get_task_addr(char* name);


struct name_address { char* name; void (*task_ptr)(int); }; 