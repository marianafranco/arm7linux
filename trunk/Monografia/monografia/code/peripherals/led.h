/**************************************************************
 * MACROS
 **************************************************************/

/* LED changing functions */

#define LEDBANK		*((unsigned *)0x03ff5008)					

#define LED_4_ON    (LEDBANK=LEDBANK|0x00000010)
#define LED_3_ON	(LEDBANK=LEDBANK|0x00000020)
#define LED_2_ON	(LEDBANK=LEDBANK|0x00000040)
#define LED_1_ON	(LEDBANK=LEDBANK|0x00000080)
#define LED_4_OFF	(LEDBANK=LEDBANK&~0x00000010)
#define LED_3_OFF	(LEDBANK=LEDBANK&~0x00000020)
#define LED_2_OFF	(LEDBANK=LEDBANK&~0x00000040)
#define LED_1_OFF	(LEDBANK=LEDBANK&~0x00000080)