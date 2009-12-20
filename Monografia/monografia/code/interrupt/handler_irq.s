;************************************************************
;	KinOS - Microkernel for ARM Evaluator 7-T
;	Seniors project - Computer Engineering
;	Escola Politecnica da USP, 2009
;	
;	Felipe Giunte Yoshida
;	Mariana Ramos Franco
;	Vinicius Tosta Ribeiro
;
;
; 
;	The program was based on the mutex program by ARM - Strategic Support Group,
;	contained on the ARM Evaluator 7-T example CD, under the folder /Evaluator7-T/
;	source/examples/mutex/ 
;************************************************************



; Hardware interrupt handling code

	IMPORT 	button_irq
	IMPORT 	timer_irq

	EXPORT 	Angel_IRQ_Address
	EXPORT 	current_thread_id
	EXPORT 	handler_board_angel
	EXPORT 	handler_board_no_angel
	EXPORT 	handler_emulator
	EXPORT 	process_control_block
	EXPORT 	thread_array
	EXPORT	force_next_thread

	; Beginning handler code
	AREA	handler_irq, CODE

force_next_thread
	ADD	r14, r14, #4	; Add 4 to the returning address in case it was not
						; called from a interruption (forced switching)
; Routine designed to the emulator, all the hardware IRQ is caused by the timer
handler_emulator
	STMFD	sp!, {r0 - r3, lr}	; Stacking r0 to r3 and the link register
	B		handler_timer		; Branch to  handler_timer

; Routine designed to the board, have the Angel handler routine, button and timer
handler_board_angel
	; Save current context for APCS
	STMFD	sp!, {r0 - r3, lr}		; Stacking r0 to r3 and the link register
	LDR 	r0, IRQStatus	 		; r0 = irq type address
	LDR 	r0, [r0]				; r0 = irq type
	TST 	r0, #0x0400				; irq type == 0x0400?
	BNE		handler_timer 			; If yes, go to handler_timer
	TST		r0, #0x0001				; irq type = 0x0001?
	BNE		handler_button			; If yes, go to handler_button
	LDMFD	sp!, {r0 - r3, lr}		; If it is not any of them, restore r0-r3 and lr
	LDR 	pc, Angel_IRQ_Address	; and branch to the Angel routine

; Routine designed to the board, not have the Angel handler routine, button and timer
handler_board_no_angel
		; Save current context for APCS
		STMFD	sp!, {r0 - r3, lr}		; Stacking r0 to r3 and the link register
		LDR 	r0, IRQStatus	 		; r0 = irq type address
		LDR 	r0, [r0]				; r0 = irq type
		TST 	r0, #0x0400				; irq type == 0x0400?
		BNE		handler_timer 			; If yes, go to handler_timer
		TST		r0, #0x0001				; irq type = 0x0001?
		BNE		handler_button			; If yes, go to handler_button
		LDMFD	sp!, {r0 - r3, lr}		; If it is not any of them, restore r0-r3 and lr
		B 		end_handler				; and return

; handler routine for the button interruption
handler_button
	BL	button_irq			; C routine	for the button
	B	no_thread_switch	; End the handler

; Timer interruption handler routine
handler_timer
	STMFD	sp!, {r4 - r12}			; Stack the rest of the registers (r4-r12)
	BL		timer_irq				; Clear timer interruption
	LDMFD	sp!, {r4 - r12}			; Load r4-12 registers again
	LDR		r0, =current_thread_id	; r0 = current_thread_id address
	LDR		r0, [r0]				; r0 = current_thread_id
									; Send to the next step r0 as the current
									; thread ID

; Finds out the next active thread id (send result in r1)
get_next_taskid_loop
	CMP 	r0, #9 					; r0 == 9? (it is the last thread?)
	BEQ		last_thread				; If yes, branch last_thread
	ADD		r1, r0, #1				; If not, r1 = r0 + 1
	B		next_thread				; and branch to next_thread
last_thread
	MOV		r1, #1					; r1 = 1
next_thread
	SUB		r2, r1, #1				; r2 = r1 - 1
	MOV		r3, #4					; r3 = 4
	MUL		r2, r3, r2				; r2 = r2 * r3
	LDR		r3, =thread_array		; r3 = thread_array bottom address
	ADD		r2, r2, r3				; r2 = r3 + r2
	LDR		r2, [r2]				; r2 = thread array content
	CMP		r2, #1					; thread array content = 1?
	BEQ		set_addresses			; If yes, branch to set_addresses
									; Send to the next step the next active
									; thread in r1
	MOV		r0, r1					; If not, r0 = r1
	B		get_next_taskid_loop	; and loop to get_next_taskid_loop

; Sets current and next thread PCB addresses
set_addresses
	LDR		r2, =current_thread_id		; r2 = current thread id address
	LDR		r2, [r2]					; r2 = current thread id
	CMP		r2, r1						; Is r2 = current thread id ==
										; next thread id
	BEQ		no_thread_switch			; If yes, branch to no_thread_switch
; Setting current_task_addr
	MOV		r0, #68						; Else start thread switch. r0 = 68
	MUL		r0,	r2, r0					; r0 = current thread id * 68
	LDR		r2, =process_control_block	; r2 = PCB bottom
	ADD		r0, r0, r2					; r0 = PCB bottom + id * 68
	LDR		r2, =current_task_addr		; r2 = current task addr addr
	STR		r0, [r2]					; current_task_addr = r0
; Setting next_task_addr
	MOV		r0, #68						; r0 = 68
	MUL		r0,	r1, r0					; r0 = next thread id * 68
	LDR		r2, =process_control_block	; r2 = PCB_bottom
	ADD		r0, r2, r0					; r0 = PCB bottom + next id * 68
	LDR		r2, =next_task_addr			; r2 = next_task_addr addr
	STR		r0, [r2]					; next_task_addr = r0

; Setting new current_thread_id
	LDR		r0, =current_thread_id		; r0 = current_thread_id
	STR		r1, [r0]					; current_thread_id = next thread id
	
; Carry out process switch
; Reset and save IRQ stack
	LDR		r0, =irq_stack_pointer		; r0 = irq_stack_pointer addr
	MOV		r1, sp						; r1 = irq stack pointer
	ADD		r1, r1, #5*4				; r1 = irq stack pointer + 5 (# of data in
										; the stack, r0-r3, lr) * 4 (size of a word)
	STR		r1, [r0]					; irq_stack_pointer = irq stack pointer
										; without the data that will be removed next
	LDMFD		sp!,{r0-r3,lr}			; Restore the remaining registers
; Load and position r13 to point into current PCB
	LDR		r13, =current_task_addr		; r13 = current task PCB bottom address address 
	LDR		r13, [r13]					; r13 = current task PCB bottom address
	SUB		r13, r13,#60				; r13 = current task PCB bottom address - 60
										; to point to the right place for the stacking
										; (next step)
; Store the current user registers in current PCB
	STMIA 	r13, {r0-r14}^				; Stacks the r0-r14 registers in the PCB
	MRS		r0, SPSR					; r0 = status register
	STMDB	r13, {r0,r14}				; Stacks r0 and r14
;Load and position r13 to point into next PCB
	LDR 	r13, =next_task_addr		; r13 = next task PCB bottom address address 
	LDR		r13, [r13]					; r13 = next task PCB bottom address 
	SUB		r13, r13,#60				; r13 = next task PCB bottom address - 60
										; to point to the right place for the stacking
										; (next step)
; Load the next task and setup PSR
	LDMNEDB	r13, {r0,r14}				; Restore r0 and r14 (IRQ mode)
	MSRNE 	spsr_cxsf, r0				; Restore status register
	LDMNEIA	r13, {r0-r14}^				; Restore r0-r14 for the user mode
	NOP									; NOP! (required for the above instruction)
; Load the IRQ stack into r13_irq
	LDR		r13, =irq_stack_pointer		; r13 = stack pointer address address
	LDR		r13,[r13]					; Restore previous stack pointer
	B		end_handler						; Go to the end

no_thread_switch
	LDMFD		sp!,{r0-r3,lr}			; Restore the remaining registers

end_handler
	SUBS 		pc, r14, #4				; Process counter = IRQ mode link register - 4
										; (-4 is required for the pipeline)

	; Data area
	AREA	irq_vars, DATA

IRQStatus				; IRQ interrupt type address
	DCD 0x03ff4004
Angel_IRQ_Address		; Reserved space for the Angel IRQ Interrupt address
	DCD 0x00000000
current_thread_id		; Context task ID 
	DCD 0x0
current_task_addr		; Address of the PCB for the current Task
	DCD 0x0
next_task_addr			; Address of the PCB for the next Task 
	DCD 0x0
irq_stack_pointer		; Copy of the IRQ stack
	DCD 0x0
process_control_block	; PCB for all the tasks (each size = 68) Offsets = bottom + 
	% 612				; 68 * process#
thread_array			; Thread status array, where each thread has one word to indicate
	% 36				; if it is active (1) or inactive (0). Offset = bottom + 4 * thread#
	
	; End of assembly code
	END