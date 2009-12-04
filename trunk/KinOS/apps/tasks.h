#include "../peripherals/segment.h"
#include "../interrupt/swi.h"

void task1 (void);
void task2 (int);
void set_segment(int);


int strcmp (char* str1, char* str2);
pt2Task  get_task_addr(char* name);


struct name_address { char* name; void (*task_ptr)(int); }; 