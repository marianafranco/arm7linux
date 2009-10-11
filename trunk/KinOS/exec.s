	EXPORT rotina_exec
	
	IMPORT handler_task_bottom
	
	AREA	exec, CODE, READONLY

; Description: Sets up TASK B Processor Control Block
; task2[-4]  = "PCB R14" = &task2
; task2[-8]  = "PCB SP"  = TASK1 SP - 4048;
; task2[-60] = "LR"      = &task2 
; task2[-64] = "SPSR"	 = %nzcvift_User32 = 0x10
	
rotina_exec
	;MOV	pc, r1

	MOV		r3, r1		; r3 = task pointer
	MOV		r4, r0		; r4 = task id
	
	; Pondo o endereço de task2 em handler_task2pcb_str - 4
	MOV		r0, r3
	ADD		r0,r0,#4
	LDR		r1, =handler_task_bottom
	SUB		r5,r4,#2
	MOV		r6,#68
	MUL		r7,r5,r6
	ADD		r7,r7,#136
	ADD		r1,r1,r7
	SUB		r1,r1,#4
	STR		r0,[r1]	

	; -- set up USER stack for TASK2 .................
	SUB		r1,r1,#4
loop
	SUB		r4,r4,#1
	CMP		r4,#0
	BEQ		end_loop
	SUB		r0,sp,#4048
	B		loop
end_loop
	STR		r0,[r1]

	; -- set up link register ............................
	SUB		r1,r1,#56
	MOV		r0,r3
	ADD		r0,r0,#4
	STR		r0,[r1]

	; -- set up SPSR .....................................
	; Obs: Todos os processos rodam no modo usuário.	
	SUB		r1,r1,#4
	MOV		r0,#0x10 
	STR		r0,[r1]
	
	BX   	lr			; return
	
	END