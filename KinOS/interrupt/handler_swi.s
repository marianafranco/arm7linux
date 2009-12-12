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


; Software interrupt handling code

	IMPORT	routine_fork
	IMPORT	routine_exec
	IMPORT	routine_exit
	IMPORT  routine_print

	EXPORT 	Angel_SWI_Address
	EXPORT 	handler_swi

	; Beginning handler code
	AREA	handler, CODE

; Software interruption routine handler
handler_swi
	STMFD 	sp!,{r0-r12,lr}			; Stack registers r0-12 and link register
	LDR		r0,[lr,#-4]				; Calculate address of SWI instruction (r0 = lr-4)
	BIC		r0,r0,#0xff000000		; Mask off top 8 bits of instruction to give SWI 
									; number
	LDR		r1, Angel_SWI_Number	; r1 = Angel SWI Number
	CMP		r0, r1					; Compare SWI number to angel interrupt number 
	BEQ		goto_angel				; If it is angel interrupt, branch to goto_angel
	MOV		r1, #0					; r1 = 0
	CMP		r0, r1					; Compare SWI number to r1
	BEQ		os_swi					; If it is OS SWI, branch to os_swi

; Go to Angel routine
goto_angel
	LDMFD	sp!,{r0-r12,lr}			; Restore registers r0-r12 and link register
	LDR		pc, Angel_SWI_Address	; Branch to the Angel

; Operating system SWI handler, identify the routine
os_swi
	LDMFD	sp!,{r0-r12,lr}		; Restore r0-r12 registers and link registers
	STMFD 	sp!,{r0-r12,lr}		; and stores them again (in order to clean the registers)
	MOV		r1,	#0				; r1 = 0
	CMP		r0, r1				; Compare the first parameter to 0
	BEQ		pre_routine_fork	; If it is equal, branch to the fork
	MOV		r1,	#1				; r1 = 1
	CMP		r0, r1				; Compare the first parameter to 1
	BEQ		pre_routine_exec	; If it is equal, branch to the exec
	MOV		r1,	#2				; r1 = 2
	CMP		r0, r1				; Compare the first parameter to 2
	BEQ		pre_routine_exit	; If it is equal, branch to the exit
	MOV		r1,	#3				; r1 = 3
	CMP		r0, r1				; Compare the first parameter to 3
	BEQ		pre_routine_print	; If it is equal, branch to the print
	LDMFD	sp!,{r0-r12,pc}^	; If it is an unidentified syscall, go back to the program,
								; restoring the registers and putting the return address in
								; the process counter

; Fork caller
pre_routine_fork
	LDMFD	sp!,{r0-r12,lr}	; Restore r0-r12 registers and link registers
	STMFD 	sp!,{r0-r12,lr}	; and stores them again (in order to clean the registers)
	B	routine_fork		; Branch to the fork C routine

; Exec caller
pre_routine_exec
	LDMFD	sp!,{r0-r12,lr}	; Restore r0-r12 registers and link registers
	STMFD 	sp!,{r0-r12,lr}	; and stores them again (in order to clean the registers)
	B	routine_exec		; Branch to the exec C routine

; Exit caller
pre_routine_exit
	LDMFD	sp!,{r0-r12,lr}	; Restore r0-r12 registers and link registers
	STMFD 	sp!,{r0-r12,lr}	; and stores them again (in order to clean the registers)
	B	routine_exit		; Branch to the exit C routine

; Print caller
pre_routine_print
	LDMFD	sp!,{r0-r12,lr}	; Restore r0-r12 registers and link registers
	STMFD 	sp!,{r0-r12,lr}	; and stores them again (in order to clean the registers)
	MOV 	r0, r2			; r0 = r2
	BL	routine_print		; Branch to the print C routine
	LDMFD	sp!,{r0-r12,pc}^; Return to the original function

	; Data area
	AREA	swi_vars, DATA

Angel_SWI_Number		; Identification number for the Angel SWI
		DCD	0x00123456
Angel_SWI_Address		; Reserved space for the Angel SWI Interrupt address
		DCD 0x00000000
		
	; End of assembly code
	END