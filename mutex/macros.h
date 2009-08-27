// Interrupt controller = 0x03ff0000

// Address of the IRQ controller (Interrupt controller+0x4004)
#define INTPND							((volatile unsigned *)0x03ff4004)
// Both are used to mask the interrupt source (Interrupt controller+0x4008)
#define INTMSK							((volatile unsigned *)0x03ff4008)
#define INT_GLOBAL						(21)

// Timer mode register (Interrupt controller+0x6000)
#define TMOD				((volatile unsigned *)0x03ff6000)  
// Holds the timer initialization value (Interrupt controller+0x6004)
#define TDATA0				((volatile unsigned *)0x03ff6004) 

// -- Generals
//#define IRQVector	0x123456
unsigned *IRQVector = (unsigned *)0x18;


