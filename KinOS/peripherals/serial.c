/*************************************************************
 *
 *	ARM Strategic Support Group
 *
 *************************************************************/

/*************************************************************
 *
 *	Module		: serial.c
 *	Description	: simple code to drive the serial port on the
 *				  Evaluator7T.
 * 	Tool Chain	: ARM Developer Suite 1.0
 * 	Platform	: Evaluator7T
 * 	History		:
 *
 *		2000-3-29 Andrew N. Sloss
 *		- started serial module
 *
 **************************************************************/
 
/**************************************************************
 * IMPORT
 **************************************************************/
 
// none...

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

/* -- serial_init -----------------------------------------------
 *
 * Description	: wait until a key is press from the host PC.
 *
 * Parameters	: unsigned int port - com port either USER/DEBUG
 *				: unsigned int baud - baud rate i.e. 9600
 * Return		: none...
 * Notes		: none...
 *
 */

void serial_init (unsigned int port, unsigned int baud)
{
   /* Disable interrupts  */
   *(volatile unsigned *) (port + UCON) = 0;

   /* Set port for 8 bit, one stop, no parity  */
   *(volatile unsigned *) (port + ULCON) = (ULCR8bits);

   /* Enable interrupt operation on UART */
   *(volatile unsigned *) (port + UCON) = UCRRxM | UCRTxM;

   /* Set baud rate  */
   *(volatile unsigned *) (port + UBRDIV) = baud;

}

/* -- serial_initcom0user --------------------------------------
 *
 * Description	: initializes the USER/COM0 serial port.
 *
 * Parameters	: unsigned baudrate - baudrate i.e. 9600
 * Return		: none...
 * Notes		: none...
 *
 */

void serial_initcom0user (unsigned baudrate)
{ 
	serial_init(UART0_BASE,baudrate); 
}

/* -- serial_initcom1debug -------------------------------------
 *
 * Description	: initializes the DEBUG/COM1 serial port.
 *
 * Parameters	: unsigned baudrate - baudrate i.e. 9600
 * Return		: none...
 * Notes		: none...
 *
 */
 
void serial_initcom1debug (unsigned baudrate)
{ serial_init(UART1_BASE,baudrate); }

/* -- serial_print ---------------------------------------------
 *
 * Description	: print out a string through the com port
 *
 * Parameters	: unsigned port - USER/DEBUG
 * 				: char *s - string to be printed out.
 * Return		: none...
 * Notes		: none...
 *
 */

void serial_print (unsigned port, char *s)
{
	while ( *s != 0 ) {
		switch (port) {
		case	COM0_USER:
		while ( TX_READY(GET_STATUS(UART0_BASE))==0);
		PUT_CHAR(UART0_BASE,*s++);
		break;
		case 	COM1_DEBUG:
		while ( TX_READY(GET_STATUS(UART1_BASE))==0);
	    PUT_CHAR(UART1_BASE,*s++);
		break;
		}
	}	
}		
	
/* -- serial_getkey --------------------------------------------
 *
 * Description	: standard implementation of getkey.
 *
 * Parameters	: none...
 * Return		: none...
 * Notes		: 
 *
 *			waits until a key is pressed then echo's back.
 *
 */	
	
void serial_getkey (void)
{
	char c;

	while ( (RX_DATA(GET_STATUS(UART0_BASE)))==0 )
	{
	
	};
		
	c = GET_CHAR(UART0_BASE);
	
	while ( TX_READY(GET_STATUS(UART0_BASE))==0);
	PUT_CHAR(UART0_BASE,c);
}



/* -- serial_getkey --------------------------------------------
 *
 * Description	: standard implementation of getkey.
 *
 * Parameters	: none...
 * Return		: none...
 * Notes		: 
 *
 *			waits until a key is pressed then echo's back.
 *
 */	
	
char serial_getcmd (void)
{
	char c;

	while ( (RX_DATA(GET_STATUS(UART0_BASE)))==0 )
	{
	
	};
		
	c = GET_CHAR(UART0_BASE);
	
	while ( TX_READY(GET_STATUS(UART0_BASE))==0);
		PUT_CHAR(UART0_BASE,c);
	
	return c;
}		
		
		
/*****************************************************************
 * END OF serial.c 
 *****************************************************************/