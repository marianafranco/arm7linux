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
	
	
;************ MARI *************
	IMPORT	Process_Table

;************ END MARI *********

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

	
	;******* MARI ************
	
	; -- Init the Process Table with the state for each process
init_process_table
	LDR		r0, =Process_Table
	MOV		r1, #1					; r1 contains the state value 0 or 1 (active)
	STR		r1, [r0]				; make the first process active
	MOV		r1, #0					; r1 = 0 (inactive)
	MOV		r2, #0					; r2 is used to pointer to the correct value in the process table
init_process_table_2
	ADD		r2, r2, #4				; r2 = 4 
	CMP		r2, #40					; r2 = 40 ?
	BEQ		end_init_process_table	; if r2 = 40, goto end
	ADD		r3, r0, r2				; else, r3 = r0 + r2
	STR		r1, [r3]				; Mem[r3] = r1 (active or inactive)
	B		init_process_table_2	; return to init_process_table_2
end_init_process_table

	;-- Teste area used to change the start state value of one process
	LDR		r0, =Process_Table
	MOV		r1, #1					; r1 is the state value, inactive or active
	MOV		r2, #4					; r2 = (task number-1) * 4
	ADD		r3, r0, r2				; r3 = r0 + r2
	STR		r1, [r3]				; Mem[r3] = r1 (active or inactive)
	
	
	;******* END MARI ********
	
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