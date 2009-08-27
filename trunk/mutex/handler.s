;  Provides an IRQ handler that both services the interrupt for
;  both the timer and button interrupt. For the timer interrupt
;  a context change occurs between two tasks A and B. 	   
;  The AREA must have 
;  - the attribute READONLY, otherwise the linker will not
;    place it in ROM.
;  - the attribute CODE, otherwise the assembler will not
;    let us put any code in this AREA

	IMPORT timer_irq
	EXPORT handler_timer
	EXPORT Angel_IRQ_Address
	EXPORT handler_currenttaskid_str
	EXPORT handler_task_bottom
	
	AREA	irq, CODE, READONLY

; -- address of the IRQ controller 
INTPND		DCD		0x03ff4004

; Services the timer interrupt and complete a context change.
handler_timer
	; Save current context for APCS
	STMFD	sp!, {r0 - r3, LR}
	; Go back to the system mode
	;MRS			r0,CPSR
	;ORR			r0,r0,#0x1F
	;MSR 			CPSR_c,r0
	; Reset the timer	
	STMFD		sp!, {r4 - r12}
	BL		timer_irq
	LDMFD		sp!, {r4 - r12}
	; Clear the interrupt
	;MOV      r0,#0
    ;MOV      r1,#0xa800000
	;STR      r0,[r1,#0xc]
	LDMFD		sp!, {r4 - r12}
	
	;-----------------------------------------------------
	; If it is any task but the last
handler_swaptofirst
	LDR		r0, =handler_currenttaskid_str
	LDR		r1,[r0]
	CMP 	r1,#9
	BNE		handler_swaptonext
;Setup context switch to TASK 1
	ADD		r1, r1, #1
	STR		r1, [r0]	
; Set current_task_addr to TASK 9
	LDR		r0, =handler_currenttaskaddr_str
	LDR		r1, =handler_task_bottom
	ADD		r1,r1,#612
	STR		r1, [r0]
; Set next_task to point to TASK 1
	LDR		r0, =handler_task_bottom
	ADD		r0,r0,#68
	LDR		r1, =handler_nexttask_str
	STR		r0, [r1]
	B		handler_contextswitch

handler_swaptonext
;Setup context switch to task n + 1
	ADD		r1, r1, #1
	STR		r1, [r0]
; Set current_task_addr to task n
	LDR		r2, =handler_currenttaskid_str
	LDR		r2, [r2]
	SUB		r2, r2, #1
	MOV		r0, #68
	MUL		r1,	r2, r0
	LDR		r0, =handler_task_bottom
	ADD		r1, r1, r0
	LDR		r0, =handler_currenttaskaddr_str
	STR		r1, [r0]
; Set next_task to point to task n + 1
	LDR		r2, =handler_currenttaskid_str
	LDR		r2, [r2]
	MOV		r0, #68
	MUL		r1,	r2, r0
	LDR		r0, =handler_task_bottom
	ADD		r1, r1, r0
	LDR		r0, =handler_nexttask_str
	STR		r1, [r0]
	B		handler_contextswitch

	;-----------------------------------------------------

; Carry out context switch
handler_contextswitch 
	; Reset and save IRQ stack
	LDR		r0, =handler_irqstack_str
	MOV		r1, sp
	ADD		r1, r1, #5*4
	STR		r1, [r0]
	; Restore the remaining registers
	LDMFD		sp!,{r0-r3,lr}
	; Load and position r13 to point into current PCB
	LDR		r13, =handler_currenttaskaddr_str
	LDR		r13, [r13]
	SUB		r13, r13,#60	
	; Store the current user registers in current PCB
	STMIA 		r13, {r0-r14}^
	MRS		r0, SPSR
	STMDB		r13, {r0,r14}
	;Load and position r13 to point into next PCB
	LDR 		r13, =handler_nexttask_str		
	LDR		r13, [r13]
	SUB		r13, r13,#60
	; Load the next task and setup PSR
	cmp		r13, #0
	LDMNEDB		r13, {r0,r14}
	MSRNE 		spsr_cxsf, r0
	LDMNEIA		r13, {r0-r14}^
	AND		r0,r0,r0 		; nop
	; Load the IRQ stack into r13_irq 
	LDR		r13, =handler_irqstack_str
	LDR		r13,[r13]
	; Return the next task
	SUBS 		pc, r14, #4
	;-----------------------------------------------------
; DATA AREA

	AREA	var, DATA, READWRITE

; Scratch location for Angel IRQ Handler address .
Angel_IRQ_Address	
	DCD 0x00000000	
; Context ID 1=TASK B 0=TASK A 
handler_currenttaskid_str
	DCD 0x0
; Address of the PCB for the next Task
handler_currenttaskaddr_str
	DCD 0x0
; Address of the PCB for the next Task 
handler_nexttask_str
	DCD 0x0
; Store a copy of the IRQ stack
handler_irqstack_str
	DCD 0x0

; +-----------------+
; | PCB Structure	|
; +-----------------+
; |	-4	| 	r14		|
; |	-8	|	r13		|
; |	-12	|	r12		|
; |	-16	|	r11		|
; |	-20	|	r10		|
; |	-24	|	r9		|
; |	-28	|	r8		|
; |	-32	|	r7		|
; |	-36	|	r6		|
; |	-40	| 	r5		|
; |	-44	|	r4		|
; |	-48	|	r3		|
; |	-52	| 	r2		|
; |	-56	| 	r1		|
; |	-60 |	r0		|
; |	-64	|	LR		|
; |	-68	|	SPSR	|
; +-----------------+
; The offsets are from (bottom + 68 * process#)

; Context PCB for all the tasks (each size = 68)
handler_task_bottom
	% 680

	END