#ifndef RPSDEF_H
#define RPSDEF_H

/*******************************************************************************/
/* RPS interrupt Controller IRQ register                                       */
/*******************************************************************************/
#define IntBase         0x0A000000
#define IRQEnable      ((volatile unsigned *)(IntBase + 0x08))
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
#define TimerPrescale8   0x08

#endif

