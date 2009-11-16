	EXPORT routine_exec
	
	IMPORT process_control_block
	
	AREA	exec, CODE, READONLY

; Description: Sets up TASK Processor Control Block
; taskPCB[-4]  = &task
; taskPCB[-8]  = "PCB SP" = SP_USER_BOTTOM - 4048;
; taskPCB[-60] = "LR" = &task 
; taskPCB[-64] = "SPSR"	= %nzcvift_User32 = 0x10


; r2 = task address
; r1 = task id 	
routine_exec
	STMFD 	sp!,{r0-r12,lr}				; save registers
	
	; -- Put the task address in task_pcb_address - 4
	MOV		r0, r2						; r0 = task address
	ADD		r0,r0,#4					; r0 = task address + 4
	LDR		r3, =process_control_block	; r3 = the start address of the PCB area
	MOV		r4,#68						; r4 = 68 (space for each process in the PCB)
	MUL		r5,r1,r4					; r5 = (task id) * 68
	ADD		r3,r3,r5					; r3 = PCB start address + r5
	SUB		r3,r3,#4					; r3 = r3 - 4
	STR		r0,[r3]						; MEM[r3] = r0

	; -- set up USER stack for the TASK .................
	SUB		r3,r3,#4					; r3 = r3 -4
loop
	SUB		r1,r1,#1					; r1 = task id - 1
	CMP		r1,#0						; r1 = 0 ??
	BEQ		end_loop					; if equal, end_loop
	MOV		r4, #0x20000				; r4 = SP_USER_BOTTOM
	SUB		r0,r4,#4048					; r0 = r4 - 4048 (space for each process in the user stack)
	B		loop						; return to loop
end_loop
	STR		r0,[r3]						; MEM[r3] = r0 (the process stack pointer)

	; -- set up link register ............................
	SUB		r3,r3,#56					; r3 = r3 - 56
	MOV		r0,r2						; r0 = task address
	ADD		r0,r0,#4					; r0 = r0 - 4
	STR		r0,[r3]						; MEM[r3] = r0

	; -- set up SPSR .....................................
	; Obs: All process run in User mode
	SUB		r3,r3,#4					; r3 = r3 - 4
	MOV		r0,#0x10 					; r0 = 0x10 (user mode)
	STR		r0,[r3]						; MEM[r3] = r0
	
	LDMFD	sp!,{r0-r12,pc}^			; return
	
	END