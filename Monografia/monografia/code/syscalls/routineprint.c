/**************************************************************
	KinOS - Microkernel for ARM Evaluator 7-T
	Seniors project - Computer Engineering
	Escola Politecnica da USP, 2009
	
	Felipe Giunte Yoshida
	Mariana Ramos Franco
	Vinicius Tosta Ribeiro
*/

/* 
	The program was based on the mutex program by ARM - Strategic Support Group,
	contained on the ARM Evaluator 7-T example CD, under the folder /Evaluator7-T/
	source/examples/mutex/ 
***************************************************************/


/**************************************************************
 * MACROS
 **************************************************************/

#define SYSCFG		(0x03ff0000)
#define UART0_BASE	(SYSCFG + 0xD000)
#define UART1_BASE 	(SYSCFG + 0xE000)

/*
 * Serial settings.......................
 */
	
#define	ULCON	0x00
#define	UCON	0x04
#define	USTAT	0x08
#define	UTXBUF	0x0C
#define	URXBUF	0x10
#define	UBRDIV	0x14

/*
 * Line control register bits............
 */
 
#define	ULCR8bits		(3)
#define	ULCRS1StopBit	(0)
#define	ULCRNoParity	(0)

/*
 * UART Control Register bits............
 */
 
#define 	UCRRxM	(1)
#define 	UCRRxSI	(1 << 2)
#define 	UCRTxM	(1 << 3)
#define 	UCRLPB	(1 << 7)

/*
 * UART Status Register bits
 */
 
#define USROverrun     	(1 << 0)
#define	USRParity      	(1 << 1)
#define	USRFraming     	(1 << 2)
#define	USRBreak       	(1 << 3)
#define	USRDTR			(1 << 4)
#define	USRRxData      	(1 << 5) 
#define	USRTxHoldEmpty 	(1 << 6)
#define	USRTxEmpty     	(1 << 7)

 /* default baud rate value */
 
#define BAUD_9600	   (162 << 4)

// UART registers are on word aligned, D8

/* UART primitives */

#define GET_STATUS(p)	(*(volatile unsigned  *)((p) + USTAT))
#define RX_DATA(s)     	((s) & USRRxData)
#define GET_CHAR(p)		(*(volatile unsigned  *)((p) + URXBUF))
#define TX_READY(s)    	((s) & USRTxHoldEmpty)
#define PUT_CHAR(p,c)  	(*(unsigned  *)((p) + UTXBUF) = (unsigned )(c))
		
#define COM1_DEBUG	(1)
#define COM0_USER	(0)


/**************************************************************
 * ROUTINES
 **************************************************************/

/*  print out a string through the user com port */
void routine_print(char *str) {
	
	while ( *str != 0 || *str != '\0') {
		while ( TX_READY(GET_STATUS(UART0_BASE))==0);
		PUT_CHAR(UART0_BASE,*str++);
	}	
	
}
