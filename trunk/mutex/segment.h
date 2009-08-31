/****************************************************************
 *
 * ARM Strategic Support Group
 * 
 ****************************************************************/

/****************************************************************
 *
 *	Module		: segment.h
 *	Description	: Segment Display header File 
 *
 *  Tool Chain	: ARM Developer Suite 1.0
 *	Platform	: Evaluator7T
 * 	Status		: Complete
 * 	History		: 
 *
 *				2000-04-04 Andrew N. Sloss
 *				- implemented
 *				
 *	Notes		:
 *
 *				This program never ends. To terminate the user 
 *				has to break in with the debugger or reset the
 *				board.
 *
 ****************************************************************/

/****************************************************************
 * IMPORT
 ****************************************************************/

// none....

/****************************************************************
 * MACROS
 ****************************************************************/
 
/* The bits taken up by the display in IODATA register */

#define	SEG_MASK	(0x1fc00)

/* define segments in terms of IO lines */

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

/****************************************************************
 * DATATYPES
 ****************************************************************/
 
// none... 

/****************************************************************
 * ROUTINES
 ****************************************************************/
 
// none... 
/****************************************************************
 * END OF SEGMENT.H
 ****************************************************************/