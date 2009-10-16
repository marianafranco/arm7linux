	EXPORT 	rotina_exit
	
	IMPORT	Process_Table
	
	AREA	exit, CODE, READONLY
	
rotina_exit
	
	MOV		r2, r0					; r2 = task id
	LDR		r0, =Process_Table
	MOV		r1, #0					; r1 is the state value = inactive
	SUB		r2, r2, #1
	MOV		r3, #4
	MUL		r4, r2, r3				; r4 = (task number-1) * 4
	ADD		r4, r0, r4				; r4 = r0 + r4
	STR		r1, [r4]				; Mem[r4] = r1 (inactive)
	
	BX		lr		; return
	
	END