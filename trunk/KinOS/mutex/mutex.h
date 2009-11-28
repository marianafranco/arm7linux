
#define WAIT 		while (semaphore==1) {} mutex_gatelock(); 
#define SIGNAL 		mutex_gateunlock(); 	

extern unsigned volatile int semaphore; // do not access directly

void mutex_gatelock (void);
void mutex_gateunlock (void);