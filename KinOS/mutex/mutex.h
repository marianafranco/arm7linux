extern unsigned volatile int semaphore_shell; // do not access directly
extern unsigned volatile int semaphore_example; // do not access directly

#define WAIT_SHELL 	  while (semaphore_shell==1) {} mutex_lock_shell(); 
#define SIGNAL_SHELL  mutex_unlock_shell(); 	

#define WAIT_EXAMPLE 	while (semaphore_example==1) {} mutex_lock_example(); 
#define SIGNAL_EXAMPLE  mutex_unlock_example(); 

void mutex_lock_shell (void);
void mutex_unlock_shell (void);
void mutex_lock_example (void);
void mutex_unlock_example (void);
