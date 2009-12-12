/****************************************************************
 * IMPORT
 ****************************************************************/

#include "constants.h"
#include "terminal.h"
#include "irq.h"
#include "button.h"
#include "segment.h"
#include "timer.h"
#include "tictactoe.h"


extern void handler_board_angel(void);
extern void handler_board_no_angel(void);
extern void handler_swi(void);
extern void handler_emulator(void);