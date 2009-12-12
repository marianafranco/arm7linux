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


; Exec system call

	EXPORT routine_exec
	
	IMPORT process_control_block
	
	; Beginning fork code
	AREA	exec, CODE

; From the call of the function: r1 = task id, r2 = task address
routine_exec
; Store variables
	STMFD 	sp!,{r0-r12,lr}				; Push r0-12 in the stack
	
	MOV		r6, r3						; r6 = value of the first argument

; Put the task address in task_pcb_address - 4 (Process counter)

	MOV		r0, r2						; r0 = task address
	ADD		r0, r0, #4					; r0 = task address + 4 (+4 due to the pipeline)
	LDR		r3, =process_control_block	; r3 = PCB bottom
	MOV		r4, #68						; r4 = 68
	MUL		r5, r1, r4					; r5 = (task id) * 68
	ADD		r3, r3, r5					; r3 = PCB bottom + (task id) * 68
	SUB		r3, r3, #4					; r3 = r3 - 4
	STR		r0, [r3]					; MEM[r3] = r0

; Set up user stack for the task
	SUB		r3, r3, #4					; r3 = r3 - 4 (stack pointer)
	MOV		r4, #0x20000				; r4 = SP_USER_BOTTOM
loop
	SUB		r1, r1, #1					; r1 = task id - 1
	CMP		r1, #0						; r1 = 0 ?
	BEQ		end_loop					; if equal, end_loop
	SUB		r4, r4, #4048				; r0 = r4 - 4048 (next stack)
	B		loop						; Go to next stack
end_loop
	STR		r4,[r3]						; MEM[r3] = r4 (the process stack pointer)

; Set up the r0
	SUB		r3,r3,#52					; r3 = r3 - 52
	STR		r6,[r3]

; Set up link register
	SUB		r3, r3, #4					; r3 = r3 - 4 (link register)
	MOV		r0, r2						; r0 = task address
	ADD		r0, r0, #4					; r0 = r0 - 4
	STR		r0, [r3]					; MEM[r3] = r0

; Set up SPSR
	SUB		r3, r3, #4					; r3 = r3 - 4
	MOV		r0, #0x10 					; r0 = 0x10 (user mode)
	STR		r0, [r3]					; MEM[r3] = r0
	
; Return
	LDMFD	sp!, {r0-r12,pc}^	; Pop r0-r12 and link register to process counter
	
	; End of assembly code
	END