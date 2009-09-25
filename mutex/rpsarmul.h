#define emulator 0

#define IRQVector (unsigned *) 0x18
#define COUNTDOWN	0x00effff0

// Emulator variables
// RPS interrupt Controller IRQ register
#define IntBase         0x0A000000
#define IRQEnableSet   ((volatile unsigned *)(IntBase + 0x08))
#define IRQEnableClear ((volatile unsigned *)(IntBase + 0x0c))
// RPS interrupt sources
#define IRQTimer1       0x0010
//  Counter/timer registers
#define TimerBase       0x0A800000
#define Timer1Load       ((volatile unsigned *)TimerBase)
#define Timer1Control    ((volatile unsigned *)(TimerBase + 0x08))
#define Timer1Clear      ((volatile unsigned *)(TimerBase + 0x0C))
// Counter/Timer control register bits 
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

// Button variables
#define IOPCON ((volatile unsigned *)(SYSCFG+0x5004))
#define INT_SW3_MASK (1)
#define IO_ENABLE_INT0 (1<<4)
#define IO_ACTIVE_HIGH_INT0 (1<<3)
#define IO_RISING_EDGE_INT0 (1)

// Dips variables
#define IOPDATA ((volatile unsigned *)(SYSCFG+0x5008))
#define SWITCH_MASK	(0xf)