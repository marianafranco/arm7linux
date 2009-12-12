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

	EXPORT 	routine_exit
	
	IMPORT	thread_array
	
	; Beginning fork code
	AREA	exit, CODE

; r1 comes as task id
routine_exit
	STMFD 	sp!,{r0-r12, lr}		; save registers
	MOV		r2, r1					; r2 = task id
	LDR		r0, =thread_array		; r0 = thread_array
	MOV		r1, #0					; r1 is the state value = inactive
	SUB		r2, r2, #1				; r2 = task id - 1
	MOV		r3, #4					; r3 = 4
	MUL		r4, r2, r3				; r4 = (task id - 1) * 4
	ADD		r4, r0, r4				; r4 = thread_array + (task id - 1) * 4
	STR		r1, [r4]				; Mem[r4] = r1 (inactive)
	
	LDMFD	sp!,{r0-r12,pc}^		; return
	
	; End of assembly code
	END