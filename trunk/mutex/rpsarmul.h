#define emulator 0

#define IRQVector (unsigned *) 0x18

/*******************************************************************************/
/* RPS interrupt Controller IRQ register                                       */
/*******************************************************************************/
#define IntBase         0x0A000000
#define IRQEnableSet   ((volatile unsigned *)(IntBase + 0x08))
#define IRQEnableClear ((volatile unsigned *)(IntBase + 0x0c))

/*******************************************************************************/
/* RPS interrupt sources                                                       */
/*******************************************************************************/
#define IRQTimer1       0x0010

/*******************************************************************************/
/*  Counter/timer registers                                                    */
/*******************************************************************************/
#define TimerBase       0x0A800000
#define Timer1Load       ((volatile unsigned *)TimerBase)
#define Timer1Control    ((volatile unsigned *)(TimerBase + 0x08))
#define Timer1Clear      ((volatile unsigned *)(TimerBase + 0x0C))

/*******************************************************************************/
/* Counter/Timer control register bits                                         */
/*******************************************************************************/
#define TimerEnable      0x80
#define TimerPeriodic    0x40
#define TimerPrescale8   0x08

// Board variables
#define SYSCFG	0x03ff0000
#define TMOD	((volatile unsigned *)(SYSCFG+0x6000))
#define INTPND	((volatile unsigned *)(SYSCFG+0x4004))
#define TDATA0	((volatile unsigned *)(SYSCFG+0x6004))
#define INTMSK	((volatile unsigned *)(SYSCFG+0x4008))
#define INT_GLOBAL	(21)