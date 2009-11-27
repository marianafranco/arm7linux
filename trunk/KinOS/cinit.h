#include "constants.h"
#include "apps/tasks.h"
#include "apps/terminal.h"
#include "interrupt/irq.h"
#include "peripherals/button.h"
#include "peripherals/segment.h"
#include "peripherals/timer.h"

extern void handler_board_angel(void);
extern void handler_board_no_angel(void);
extern void handler_swi(void);
extern void handler_emulator(void);