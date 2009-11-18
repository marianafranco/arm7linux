/********* GENERAL VARIABLES *********/
/* Defines if the program is running on: */
/* 0 - Evaluator 7-T board */
/* 1 - CodeWarrior ARMUlator */
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
/* Button addresses */
#define IRQButtonControl			(volatile unsigned *) 0x03ff5004
/* Segment addresses */
#define IOPMod          			(volatile unsigned *)0x03ff5000
 /* The bits taken up by the display in IOData register */
#define	Segment_mask	0x1FC00
/* Define segments in terms of IO lines */
#define	SEG_A		(1<<10)
#define	SEG_B		(1<<11)
#define	SEG_C		(1<<12)
#define	SEG_D		(1<<13)
#define	SEG_E		(1<<14)
#define	SEG_F		(1<<16)
#define	SEG_G		(1<<15)
#define	DISP_0		(SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F)
#define	DISP_1		(SEG_B|SEG_C)
#define	DISP_2		(SEG_A|SEG_B|SEG_D|SEG_E|SEG_G)
#define	DISP_3		(SEG_A|SEG_B|SEG_C|SEG_D|SEG_G)
#define	DISP_4		(SEG_B|SEG_C|SEG_F|SEG_G)
#define	DISP_5		(SEG_A|SEG_C|SEG_D|SEG_F|SEG_G)
#define	DISP_6		(SEG_A|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G)
#define	DISP_7		(SEG_A|SEG_B|SEG_C)
#define	DISP_8		(SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G)
#define	DISP_9		(SEG_A|SEG_B|SEG_C|SEG_D|SEG_F|SEG_G)
#define	DISP_A		(SEG_A|SEG_B|SEG_C|SEG_E|SEG_F|SEG_G)
#define	DISP_B		(SEG_C|SEG_D|SEG_E|SEG_F|SEG_G)
#define	DISP_C		(SEG_A|SEG_D|SEG_E|SEG_F)
#define	DISP_D		(SEG_B|SEG_C|SEG_D|SEG_E|SEG_G)
#define	DISP_E		(SEG_A|SEG_D|SEG_E|SEG_F|SEG_G)
#define	DISP_F		(SEG_A|SEG_E|SEG_F|SEG_G)