#include "constants.h"
#include "apps/tasks.h"
#include "interrupt/irq.h"
#include "peripherals/button.h"
#include "peripherals/segment.h"
#include "peripherals/timer.h"

extern void handler_board(void);
extern void handler_swi(void);
extern void handler_emulator(void);