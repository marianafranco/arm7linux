; Startup code to initialize the embedded C library and 
; setup PCB for task B.
	
	IMPORT	task2
	IMPORT	task3
	IMPORT	task4
	IMPORT	task5
	IMPORT	task6
	IMPORT	task7
	IMPORT	task8
	IMPORT	task9
	IMPORT	handler_currenttaskid_str
	IMPORT handler_task_bottom

	AREA asm_code, CODE

; If assembled with TASM the variable {CONFIG} will be set to 16
; If assembled with ARMASM the variable {CONFIG} will be set to 32
; Set the variable THUMB to TRUE or false depending on whether the
; file is being assembled with TASM or ARMASM.

	GBLL THUMB
	[ {CONFIG} = 16

THUMB SETL {TRUE}
	
; If assembling with TASM go into 32 bit mode as the Armulator will
; start up the program in ARM state.

	CODE32
	|
THUMB SETL {FALSE}
	]
	
	IMPORT C_Entry
	
	ENTRY
|__init|

; Set up the stack pointer to point to the 512K (Evaluator7T top of 
; memory.

	; Setting up IRQ stack
	MOV		r2,	#0xc0|0x12
	MSR		CPSR_c, r2
	MOV		sp, #0x8000
	
	; Setting up user stack
	MOV		r2, #0xc0|0x1f
	MSR		CPSR_c, r2
	MOV		sp, #0x20000
	
	;Setting up SVC stack
	MOV		r2,	#0xc0|0x13
	MSR		CPSR_c, r2
	MOV		r1, #0x8000
	SUB		r1, r1, #128
	MOV		sp, r1

; Description: Sets up TASK B Processor Control Block
; task2[-4]  = "PCB R14" = &task2
; task2[-8]  = "PCB SP"  = TASK1 SP - 4048;
; task2[-60] = "LR"      = &task2 
; task2[-64] = "SPSR"	 = %nzcvift_User32 = 0x10

startup_pcb
	
	;-----------------------------------------------------	
	; Pondo o endereço de task2 em handler_task2pcb_str - 4

	LDR		r0, =task2
	ADD		r0,r0,#4
	LDR		r1, =handler_task_bottom
	ADD		r1,r1,#136
	SUB		r1,r1,#4
	STR		r0,[r1]	

	; -- set up USER stack for TASK2 .................

	SUB		r1,r1,#4
	SUB		r0,sp,#4048
	STR		r0,[r1]

	; -- set up link register ............................

	SUB		r1,r1,#56
	LDR		r0,=task2
	ADD		r0,r0,#4
	STR		r0,[r1]

	; -- set up SPSR .....................................

	SUB		r1,r1,#4
	MOV		r0,#0x10 
	STR		r0,[r1]
	;-----------------------------------------------------
	; Pondo o endereço de task3 em handler_task3pcb_str - 4

	LDR		r0, =task3
	ADD		r0,r0,#4
	LDR		r1, =handler_task_bottom
	ADD		r1,r1,#204
	SUB		r1,r1,#4
	STR		r0,[r1]	

	; -- set up USER stack for TASK3 .................

	SUB		r1,r1,#4
	SUB		r0,sp,#4048
	SUB		r0,r0,#4048
	STR		r0,[r1]

	; -- set up link register ............................

	SUB		r1,r1,#56
	LDR		r0,=task3
	ADD		r0,r0,#4
	STR		r0,[r1]

	; -- set up SPSR .....................................

	SUB		r1,r1,#4
	MOV		r0,#0x10 
	STR		r0,[r1]
	;-----------------------------------------------------
	; Pondo o endereço de task4 em handler_task4pcb_str - 4

	LDR		r0, =task4
	ADD		r0,r0,#4
	LDR		r1, =handler_task_bottom
	ADD		r1,r1,#272
	SUB		r1,r1,#4
	STR		r0,[r1]	

	; -- set up USER stack for TASK4 .................

	SUB		r1,r1,#4
	SUB		r0,sp,#4048
	SUB		r0,r0,#4048
	SUB		r0,r0,#4048
	STR		r0,[r1]

	; -- set up link register ............................

	SUB		r1,r1,#56
	LDR		r0,=task4
	ADD		r0,r0,#4
	STR		r0,[r1]

	; -- set up SPSR .....................................

	SUB		r1,r1,#4
	MOV		r0,#0x10 
	STR		r0,[r1]
	;-----------------------------------------------------
	; Pondo o endereço de task5 em handler_task5pcb_str - 4

	LDR		r0, =task5
	ADD		r0,r0,#4
	LDR		r1, =handler_task_bottom
	ADD		r1,r1,#340
	SUB		r1,r1,#4
	STR		r0,[r1]	

	; -- set up USER stack for TASK5 .................

	SUB		r1,r1,#4
	SUB		r0,sp,#4048
	SUB		r0,r0,#4048
	SUB		r0,r0,#4048
	SUB		r0,r0,#4048
	STR		r0,[r1]

	; -- set up link register ............................

	SUB		r1,r1,#56
	LDR		r0,=task5
	ADD		r0,r0,#4
	STR		r0,[r1]

	; -- set up SPSR .....................................

	SUB		r1,r1,#4
	MOV		r0,#0x10 
	STR		r0,[r1]
	;-----------------------------------------------------
	; Pondo o endereço de task6 em handler_task6pcb_str - 4

	LDR		r0, =task6
	ADD		r0,r0,#4
	LDR		r1, =handler_task_bottom
	ADD		r1,r1,#408
	SUB		r1,r1,#4
	STR		r0,[r1]	

	; -- set up USER stack for TASK6 .................

	SUB		r1,r1,#4
	SUB		r0,sp,#4048
	SUB		r0,r0,#4048
	SUB		r0,r0,#4048
	SUB		r0,r0,#4048
	SUB		r0,r0,#4048
	STR		r0,[r1]

	; -- set up link register ............................

	SUB		r1,r1,#56
	LDR		r0,=task6
	ADD		r0,r0,#4
	STR		r0,[r1]

	; -- set up SPSR .....................................

	SUB		r1,r1,#4
	MOV		r0,#0x10 
	STR		r0,[r1]
	;-----------------------------------------------------
	; Pondo o endereço de task7 em handler_task7pcb_str - 4

	LDR		r0, =task7
	ADD		r0,r0,#4
	LDR		r1, =handler_task_bottom
	ADD		r1,r1,#476
	SUB		r1,r1,#4
	STR		r0,[r1]	

	; -- set up USER stack for TASK7 .................

	SUB		r1,r1,#4
	SUB		r0,sp,#4048
	SUB		r0,r0,#4048
	SUB		r0,r0,#4048
	SUB		r0,r0,#4048
	SUB		r0,r0,#4048
	SUB		r0,r0,#4048
	STR		r0,[r1]

	; -- set up link register ............................

	SUB		r1,r1,#56
	LDR		r0,=task7
	ADD		r0,r0,#4
	STR		r0,[r1]

	; -- set up SPSR .....................................

	SUB		r1,r1,#4
	MOV		r0,#0x10 
	STR		r0,[r1]
	;-----------------------------------------------------
	; Pondo o endereço de task8 em handler_task8pcb_str - 4

	LDR		r0, =task8
	ADD		r0,r0,#4
	LDR		r1, =handler_task_bottom
	ADD		r1,r1,#544
	SUB		r1,r1,#4
	STR		r0,[r1]	

	; -- set up USER stack for TASK8 .................

	SUB		r1,r1,#4
	SUB		r0,sp,#4048
	SUB		r0,r0,#4048
	SUB		r0,r0,#4048
	SUB		r0,r0,#4048
	SUB		r0,r0,#4048
	SUB		r0,r0,#4048
	SUB		r0,r0,#4048
	STR		r0,[r1]

	; -- set up link register ............................

	SUB		r1,r1,#56
	LDR		r0,=task8
	ADD		r0,r0,#4
	STR		r0,[r1]

	; -- set up SPSR .....................................

	SUB		r1,r1,#4
	MOV		r0,#0x10 
	STR		r0,[r1]
	;-----------------------------------------------------
	; Pondo o endereço de task9 em handler_task9pcb_str - 4

	LDR		r0, =task9
	ADD		r0,r0,#4
	LDR		r1, =handler_task_bottom
	ADD		r1,r1,#612
	SUB		r1,r1,#4
	STR		r0,[r1]	

	; -- set up USER stack for TASK9 .................

	SUB		r1,r1,#4
	SUB		r0,sp,#4048
	SUB		r0,r0,#4048
	SUB		r0,r0,#4048
	SUB		r0,r0,#4048
	SUB		r0,r0,#4048
	SUB		r0,r0,#4048
	SUB		r0,r0,#4048
	SUB		r0,r0,#4048
	STR		r0,[r1]

	; -- set up link register ............................

	SUB		r1,r1,#56
	LDR		r0,=task9
	ADD		r0,r0,#4
	STR		r0,[r1]

	; -- set up SPSR .....................................

	SUB		r1,r1,#4
	MOV		r0,#0x10 
	STR		r0,[r1]
	;-----------------------------------------------------

	; -- set the current ID to TASK1

	LDR		r0, =handler_currenttaskid_str
	MOV		r1, #1
	STR		r1, [r0]

; -- startup initialization complete ...........................

	LDR 	lr, =C_Entry
	[ THUMB

; If building a Thumb version pass control to C_entry Using the BX
; instruction so the processor will switch to THUMB state.

	BX lr
	|

; Otherwise just pass control to C_Entry in ARM state.

	MOV pc, lr
	]
	 
	END