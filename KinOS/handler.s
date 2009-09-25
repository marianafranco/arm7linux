	IMPORT timer_irq
	EXPORT handler
	EXPORT handler_currenttaskid_str
	EXPORT handler_task_bottom
	EXPORT Angel_IRQ_Address
	EXPORT handler_emulator
	
	
;*********** MARI ******************
	EXPORT	Process_Table
	
;	EXPORT	PtrStateTask1
;	EXPORT	PtrStateTask2
;	EXPORT	PtrStateTask3
;	EXPORT	PtrStateTask4
;	EXPORT	PtrStateTask5
;	EXPORT	PtrStateTask6
;	EXPORT	PtrStateTask7
;	EXPORT	PtrStateTask8
;	EXPORT	PtrStateTask9
;	
;*********** END MARI **************
	
	
	AREA	irq, CODE, READONLY

INTPND		DCD		0x03ff4004

handler_emulator
	; Save current context for APCS
	STMFD	sp!, {r0 - r3, LR}
	B		handler_timer

; Services the timer interrupt and complete a context change.
handler
	; Save current context for APCS
	STMFD	sp!, {r0 - r3, LR}
	; If it is a timer interrupt, branch
	LDR 	r0, INTPND	 
	LDR 	r0, [r0]		
	TST 	r0, #0x0400
	BNE		handler_timer 
	; Otherwise, go to the angel
	LDMFD	sp!, {r0 - r3, lr}	
	LDR 	pc, Angel_IRQ_Address
	
handler_timer
	; Reset the timer	
	STMFD		sp!, {r4 - r12}
	BL		timer_irq
	LDMFD		sp!, {r4 - r12}
	; If it is not the last task, go to handler_swaptonext
	LDR		r0, =handler_currenttaskid_str
	LDR		r1,[r0]

;*********** MARI ******************
	B		get_next_taskid_1
	
get_next_taskid_1
	CMP 	r1, #9
	BNE		get_next_taskid_2
	B		get_next_taskid_3
	
get_next_taskid_2
	ADD		r3, r1, #1			;r3 guarda o id do proximo processo
	B		get_next_taskid_4	

get_next_taskid_3
	MOV		r3, #1
	
get_next_taskid_4
	SUB		r4, r3, #1
	MOV		r5, #4
	MUL		r6, r4, r5
	LDR		r5, =Process_Table
	ADD		r5, r5, r6
	LDR		r4, [r5]
	CMP		r4, #1
	BNE		get_next_taskid_5
	B		end_get_nexttaskid

get_next_taskid_5
	MOV		r1, r3
	B		get_next_taskid_1
	
end_get_nexttaskid

handler_next_process
	;Setup context switch to TASK 1
	;STR		r3, [r0]
	
	; Set current_task_addr to task n
	LDR		r2, =handler_currenttaskid_str
	LDR		r2, [r2]
	SUB		r2, r2, #1
	MOV		r0, #68
	MUL		r1,	r2, r0
	LDR		r0, =handler_task_bottom
	ADD		r1, r1, r0
	LDR		r0, =handler_currenttaskaddr_str
	STR		r1, [r0]

	; Set next_task to point to task n + 1
	MOV		r2, r3
	;LDR		r2, [r2]
	SUB		r2, r2, #1
	MOV		r0, #68
	MUL		r1,	r2, r0
	LDR		r0, =handler_task_bottom
	ADD		r1, r1, r0
	LDR		r0, =handler_nexttask_str
	STR		r1, [r0]
	
	STR		r3, [r0]		; id currrent = r3
	B		handler_contextswitch
	
	


;*********** END MARI **************
	
	CMP 	r1,#9
	BNE		handler_swaptonext
	B		handler_swaptofirst
	
; If it is any task but the last
handler_swaptofirst
	;Setup context switch to TASK 1
	MOV		r1, #1
	STR		r1, [r0]	
	; Set current_task_addr to TASK 9
	LDR		r0, =handler_currenttaskaddr_str
	LDR		r1, =handler_task_bottom
	ADD		r1,r1,#612
	STR		r1, [r0]
	; Set next_task to point to TASK 1
	LDR		r0, =handler_task_bottom
	ADD		r0,r0,#68
	LDR		r1, =handler_nexttask_str
	STR		r0, [r1]
	B		handler_contextswitch

; Switch to the next task
handler_swaptonext
	;Setup context switch to task n + 1
	ADD		r1, r1, #1
	STR		r1, [r0]
	; Set current_task_addr to task n
	LDR		r2, =handler_currenttaskid_str
	LDR		r2, [r2]
	SUB		r2, r2, #1
	MOV		r0, #68
	MUL		r1,	r2, r0
	LDR		r0, =handler_task_bottom
	ADD		r1, r1, r0
	LDR		r0, =handler_currenttaskaddr_str
	STR		r1, [r0]
	; Set next_task to point to task n + 1
	LDR		r2, =handler_currenttaskid_str
	LDR		r2, [r2]
	MOV		r0, #68
	MUL		r1,	r2, r0
	LDR		r0, =handler_task_bottom
	ADD		r1, r1, r0
	LDR		r0, =handler_nexttask_str
	STR		r1, [r0]
	B		handler_contextswitch



; Carry out process switch
handler_contextswitch 
	; Reset and save IRQ stack
	LDR		r0, =handler_irqstack_str
	MOV		r1, sp
	ADD		r1, r1, #5*4
	STR		r1, [r0]
	; Restore the remaining registers
	LDMFD		sp!,{r0-r3,lr}
	; Load and position r13 to point into current PCB
	LDR		r13, =handler_currenttaskaddr_str
	LDR		r13, [r13]
	SUB		r13, r13,#60	
	; Store the current user registers in current PCB
	STMIA 		r13, {r0-r14}^
	MRS		r0, SPSR
	STMDB		r13, {r0,r14}
	;Load and position r13 to point into next PCB
	LDR 		r13, =handler_nexttask_str		
	LDR		r13, [r13]
	SUB		r13, r13,#60
	; Load the next task and setup PSR
	cmp		r13, #0
	LDMNEDB		r13, {r0,r14}
	MSRNE 		spsr_cxsf, r0
	LDMNEIA		r13, {r0-r14}^
	AND		r0,r0,r0 		; nop
	; Load the IRQ stack into r13_irq 
	LDR		r13, =handler_irqstack_str
	LDR		r13,[r13]
	; Return the next task
	SUBS 		pc, r14, #4









	; DATA AREA

	AREA	var, DATA, READWRITE

Angel_IRQ_Address	
	DCD 0x00000000
; Context task ID 
handler_currenttaskid_str
	DCD 0x0
; Address of the PCB for the next Task
handler_currenttaskaddr_str
	DCD 0x0
; Address of the PCB for the next Task 
handler_nexttask_str
	DCD 0x0
; Store a copy of the IRQ stack
handler_irqstack_str
	DCD 0x0
; Context PCB for all the tasks (each size = 68) Offsets are from (bottom + 68 * process#)
handler_task_bottom
	% 680
	
;********** MARI ******************	
	
;--- Process Table ----;
	AREA	ProcessTable, DATA, READWRITE
Process_Table
	% 40
	

;	DCD		PtrStateTask1
;	DCD		PtrStateTask2
;	DCD		PtrStateTask3
;	DCD		PtrStateTask4
;	DCD		PtrStateTask5
;	DCD		PtrStateTask6
;	DCD		PtrStateTask7
;	DCD		PtrStateTask8
;	DCD		PtrStateTask9
;
;PtrStateTask1
;	DCD     0x1
;
;PtrStateTask2
;	DCD     0x0
;
;PtrStateTask3
;	DCD     0x0
;
;PtrStateTask4
;	DCD     0x0
;
;PtrStateTask5
;	DCD     0x0
;
;PtrStateTask6
;	DCD     0x0
;
;PtrStateTask7
;	DCD     0x0
;
;PtrStateTask8
;	DCD     0x0
;
;PtrStateTask9
;	DCD     0x0



;********** END MARI ***************


	END