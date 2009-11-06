	EXPORT 	routine_exit
	
	IMPORT	thread_array
	
	AREA	exit, CODE, READONLY
	
routine_exit
	STMFD 	sp!,{r0-r12,lr}
	MOV		r2, r1					; r2 = task id
	LDR		r0, =thread_array
	MOV		r1, #0					; r1 is the state value = inactive
	SUB		r2, r2, #1
	MOV		r3, #4
	MUL		r4, r2, r3				; r4 = (task number-1) * 4
	ADD		r4, r0, r4				; r4 = r0 + r4
	STR		r1, [r4]				; Mem[r4] = r1 (inactive)
	
	LDMFD	sp!,{r0-r12,pc}^		; return
	
	END