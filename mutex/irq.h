/* irq_ser handles the counter timer.
   Used to time a sequence of code. As well as servicing the irq interrupts */

/* Call only once, at system initialization. Initializes
   internal variables. */
extern void irq_init(void);	