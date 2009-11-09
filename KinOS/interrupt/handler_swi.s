; Software interrupt handling code

	IMPORT	routine_fork
	IMPORT	routine_exec
	IMPORT	routine_exit

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
	
goto_angel
	LDMFD	sp!,{r0-r12,lr}			;Restore registers for Angel...
	LDR		pc, Angel_SWI_Address	;if eq then branch to the Angel SWI
os_swi							;Non Angel SWI
	LDMFD	sp!,{r0-r12,lr}
	STMFD 	sp!,{r0-r12,lr}
	MOV		r1,	#0
	CMP		r0, r1
	BEQ		pre_routine_fork
	MOV		r1,	#1
	CMP		r0, r1
	BEQ		pre_routine_exec
	MOV		r1,	#2
	CMP		r0, r1
	BEQ		pre_routine_exit

pre_routine_fork
	LDMFD	sp!,{r0-r12,lr}
	STMFD 	sp!,{r0-r12,lr}
	B	routine_fork
	
pre_routine_exec
	LDMFD	sp!,{r0-r12,lr}
	STMFD 	sp!,{r0-r12,lr}
	B	routine_exec

pre_routine_exit
	LDMFD	sp!,{r0-r12,lr}
	STMFD 	sp!,{r0-r12,lr}
	B	routine_exit
	
	AREA	var1, DATA, READWRITE
	
Angel_SWI_Number
		DCD	0x00123456
	; Chained Angel SWI Interrupt address
Angel_SWI_Address
		DCD 0x00000000	
	
	END