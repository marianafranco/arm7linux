/********* GENERAL VARIABLES *********/
/* Defines if the program is running on CodeWarrior ARMUlator (0) or the Evaluator 7-T board (1) */
#define emulator	1
/* The number of the operating system software interrupt */
#define	OS_SWI		0
/* Interrupt table SWI instruction position */
#define SWIVector 	(unsigned *) 0x08
/* Interrupt table IRQ instruction position */
#define IRQVector	(unsigned *) 0x18
/* Time set for the timer */
#define COUNTDOWN	0x00effff0

/********* EMULATOR VARIABLES *********/
/* Timer interrupt ID */
#define IRQTimer			0x0010
/* IRQ interrupt controller addresses */
#define IRQEnableSet			(volatile unsigned *) 0x0A000008
#define IRQEnableClear			(volatile unsigned *) 0x0A00000C
/*  Timer registers */
#define EmulatorIRQTimerLoad	(volatile unsigned *) 0x0A800000
#define EmulatorIRQTimerControl	(volatile unsigned *) 0x0A800008
#define IRQTimerClear			(volatile unsigned *) 0x0A80000C

/********* BOARD VARIABLES *********/
/* Inoput/output data address */
#define IOData 						(volatile unsigned *) 0x03ff5008
/* IRQ interrupt controller addresses */
#define IRQStatus					(volatile unsigned *) 0x03ff4004
/*  Timer registers */
#define TimerEnableSet				(volatile unsigned *) 0x03ff6000
#define EvaluatorIRQTimerLoad		(volatile unsigned *) 0x03ff6004
#define EvaluatorIRQTimerControl	(volatile unsigned *) 0x03ff4008
// Button addresses
#define IRQButtonControl			(volatile unsigned *) 0x03ff5004