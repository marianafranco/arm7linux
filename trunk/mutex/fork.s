	IMPORT	Process_Table
	IMPORT	handler_task_bottom
	IMPORT	handler_currenttaskid_str
	
	EXPORT	routine_fork

	AREA	fork, CODE, READONLY
	
routine_fork
	STMFD 	sp!,{r0-r12,lr}
	STMFD 	sp!,{r0-r12}
	STMFD 	sp!,{lr} 
	NOP
	; Finds the first available space in the process table (return id in r0 and its address in r1)
	LDR		r1, =Process_Table
	MOV		r0,	#1
routine_fork_loop
	LDR		r2, [r1]
	CMP		r2,	#0
	BEQ		pcb_bottom
	ADD		r0,	r0,	#1
	ADD		r1,	r1,	#4
	B		routine_fork_loop
pcb_bottom
; Get the bottom of the PCB (return bottom in r2)
	LDR		r2,	=handler_task_bottom
	MOV		r3,	#68
	MUL		r3,	r0, r3
	ADD		r2,	r2,	r3
; Duplicate the stack content
; Descobre o tamanho da pilha (r5)
	; Pega conteudo de R13 do modo usuario (r3)
	SUB		r13,r13,#4
	STMIA 		r13, {r13}^
	NOP
	LDMFD	sp!,{r3}
	; Pega base do modo de usuario (r4)
	MOV		r4,#0x20000
	MOV		r5,#4048
	LDR		r6, =handler_currenttaskid_str
	LDR		r6,[r6]
	SUB		r6,	r6,	#1
	MUL		r5,	r6,	r5
	SUB		r4,	r4,	r5
; Começa a copiar a pilha
	MOV		r6,#0x20000
	MOV		r5,#4048
	SUB		r7,	r0,	#1
	MUL		r5,	r7,	r5
	SUB		r6,	r6,	r5
loop_stack_copy
	LDR		r5,	[r4]
	STR		r5,[r6]
	CMP		r4,	r3
	BEQ		set_stack_pointer
	SUB		r6,	r6,	#4
	SUB		r4,	r4,	#4
	B		loop_stack_copy
; Set the stack pointer to the same point 
; Descobre a base da pilha nova (r6)
set_stack_pointer ;
; Começa a popular o PCB de baixo p/ cima
;SPSR
	SUB		r2,	r2,	#68
	MOV		r7,#0x10 
	STR		r7,[r2]
;Stack pointer (r13)
	ADD		r2,	r2,	#60 
	STR		r6,[r2]
;r14 and LR (keep r7, as it is the return address)
	ADD		r2,	r2,	#4
	LDMFD	sp!,{r7}
	STR		r7,[r2]
	SUB		r2,	r2,	#60
	STR		r7,[r2]
;Registers
	MOV		r9,	#0
	MOV		r10,#12
registers_loop
	ADD		r2,	r2,	#4
	LDMFD	sp!,{r8}
	STR		r8,[r2]
	CMP		r9,	r10
	BEQ 	final_jump
	ADD		r9,	r9,	#1
	B		registers_loop
final_jump
	MOV		r11,#1
	STR		r11,[r1]
	LDMFD	sp!,{r0-r12,pc}^
	
		
	; Return process ID
	
	END