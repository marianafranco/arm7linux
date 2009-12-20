/****************************************************************
 * ROUTINES
 ****************************************************************/

/* Reads a string from the COM0 port */
void getcommand(char *cmd, int length);

/* The shell routine */
void shell (void);

/* Kills a running process */
void run_end(char *arg);

/* Sets the state (active or inactive) in the tasks struct */
void set_state(int pid, int state);