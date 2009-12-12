;************************************************************************************
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
;************************************************************************************


; Fork system call

	IMPORT	thread_array
	IMPORT	process_control_block
	IMPORT	current_thread_id
	
	EXPORT	routine_fork

	; Beginning fork code
	AREA	fork, CODE
	
; Routine to duplicate a process code
routine_fork
; Stacks current state twice
	STMFD 	sp!,{r1-r12,lr}		; Stacks the link register and r1-r12
	STMFD 	sp!,{r0-r12}		; Stacks r0-r12
	STMFD 	sp!,{lr} 			; Stacks the link register (In a separate instruction
								; to stack it in the top)
								
; Finds the first available space in the process table (return id in r0 and its address in r1)
	LDR		r1, =thread_array	; r1 = bottom of the thread array address
	MOV		r0,	#1				; r0 = 1
routine_fork_loop
	LDR		r2, [r1]			; r2 = thread array position
	CMP		r2,	#0				; r2 = 0?
	BEQ		pcb_bottom			; If the position is availabe (r2 = 0), go to pcb_bottom
	ADD		r0,	r0,	#1			; r0 = r0 + 1 (next id)
	CMP		r0, #10				; Is this the last thread slot being checked?
	BEQ		fork_fail			; if it is, there is no available slot, go to fork_fail
	ADD		r1,	r1,	#4			; r1 = r1 + 4 (next address)
	B		routine_fork_loop	; Check next slot (go to routine_fork_loop)

; Get the PCB bottom of the new process (return it in r2)
pcb_bottom
	LDR		r2,	=process_control_block	; r2 = pcb_bottom
	MOV		r3,	#68						; r3 = 68
	MUL		r3,	r0, r3					; r3 = 68 * available thread id
	ADD		r2,	r2,	r3					; r2 = pcb bottom + (thread id * 68)

; Retrieves user mode stack pointer (returns it in r3)
	SUB		r13, r13, #4	; Opens a space in the stack
	STMIA 	r13, {r13}^		; Store user mode stack pointer in the SVC stack
	NOP						; No operation (necessary for the above instruction)
	LDMFD	sp!,{r3}		; r3 = user mode stack pointer

; Retrieves user mode stack base (returns in r4)
	MOV		r4, #0x20000			; r4 = 0x20000 (User mode stack pointer base)
	MOV		r6, #4048				; r6 = 4048 (Distance between each thread stack)
	LDR		r5, =current_thread_id	; r5 = current thread id address
	LDR		r5, [r5]				; r5 = current thread id
	SUB		r5,	r5,	#1				; r5 = current thread id - 1
	MUL		r6,	r5,	r6				; r6 = (current thread id - 1) * 4048
	SUB		r4,	r4,	r6				; r4 = 0x20000 - (current thread id - 1) * 4048
									; (this is the base of the current thread stack)

; Retrieves new thread stack base (returns in r5)
	MOV		r5, #0x20000	; r5 = 0x20000 (User mode stack pointer base)
	MOV		r6, #4048		; r6 = 4048 (Distance between each thread stack)
	SUB		r7,	r0,	#1		; r7 = new thread id - 1
	MUL		r6,	r7,	r6		; r6 = (new thread id - 1) * 4048
	SUB		r5,	r5,	r6		; r5 = 0x20000 - ((new thread id - 1) * 4048)

; Duplicates stack
loop_stack_copy
	LDR		r6,	[r4]			; r6 = original stack data
	STR		r6, [r5]			; Stores data in new stack (stack_top = r6)
	CMP		r4,	r3				; Is this the top of the stack? (r4 == r3?)
	BEQ		build_new_pcb		; if it is, branch to build_new_pcb 
	SUB		r5,	r5,	#4			; if not, go to next space in the new stack (r5 = r5 - 4)
	SUB		r4,	r4,	#4			; and next data in the original stack (r4 = r4 - 4)
	B		loop_stack_copy		; restart sequence (go to loop_stack_copy)

build_new_pcb
; Store SPSR
	SUB		r2,	r2,	#68	; r2 = r2 - 68 (r2 = PCB[-68] address)
	MOV		r3, #0x10 	; r3 = #0x10 (User mode)
	STR		r3, [r2]	; PCB[-68] = #0x10

; Store stack pointer
	ADD		r2,	r2,	#60	; r2 = r2 + 60 (r2 = PCB[-8] address)
	STR		r5, [r2]	; PCB[-8] = new stack pointer

; Stores r14 and LR
	ADD		r2,	r2,	#4	; r2 = r2 + 4 (r2 = PCB[-4] address)
	LDMFD	sp!, {r3}	; Restore link register from the stack to r3
	ADD		r3, r3, #4	; r3 = r3 + 4 (due to the pipeline)
	STR		r3, [r2]	; PCB[-4] = return address
	SUB		r2,	r2,	#60	; r2 = r2 - 60 (r2 = PCB[-64] address)
	STR		r3, [r2]	; PCB[-64] = return address

; Copy registers
	MOV		r3,	#0		; r3 = 0
	MOV		r4, #12		; r4 = 12
registers_loop
	ADD		r2,	r2,	#4		; r2 = r2 + 4 (Next PCB register space)
	LDMFD	sp!, {r5}		; Restore register from the stack to r5
	STR		r5, [r2]		; Store register in the PCB
	CMP		r3,	r4			; r12 was copied? (r3 == r4?)
	BEQ 	enable_thread	; If yes, go to enable_thread
	ADD		r3,	r3,	#1		; r3 = r3 + 1 (Next register)
	B		registers_loop	; Copy next register

; Enable thread in the thread vector
enable_thread
	MOV		r2, #1				; r2 = 1
	STR		r2, [r1]			; New process in thread array = 1
	LDMFD	sp!, {r1-r12,pc}^	; Restore all the registers but r0
	 							; (it contains the new process id)

; Case when there is no thread space
fork_fail
	LDMFD	sp!, {lr}		; Restore link register
	LDMFD	sp!, {r0-r12}	; Restore r0-r12
	LDMFD	sp!, {r1-r12}	; Restore r1-r12
	MOV		r0, #0xFFFFFFFF	; r0 = -1 (r0 is the return value)
	LDMFD	sp!, {pc}^		; Restore return address to the process counter
	
	; End of assembly code
	END