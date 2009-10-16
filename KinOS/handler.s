	IMPORT timer_irq
	IMPORT button_irq
	IMPORT swi_chandler
	
	EXPORT handler
	EXPORT handler_emulator
	EXPORT handler_currenttaskid_str
	EXPORT handler_task_bottom
	EXPORT Angel_IRQ_Address
	EXPORT handler_swi
	EXPORT Angel_SWI_Address
	
;*********** MARI ******************
	EXPORT	Process_Table

;*********** END MARI **************
	
	AREA	irq, CODE, READONLY

INTPND		DCD		0x03ff4004

handler_swi
	STMFD 	sp!,{r0-r12,lr}			;Store registers
	STMFD	sp!, {r0 - r11}
	LDR		r0,[lr,#-4]				;Calculate address of SWI instruction
	BIC		r0,r0,#0xff000000		;Mask off top 8 bits of instruction to give SWI 
									;number
	LDR		r1, Angel_SWI_Number	;Get Angel SWI Number
	CMP		r0, r1					;Intercept Angel SWI Early 
	BNE		user_swis
	LDMFD	sp!, {r0 - r11}	
	LDMFD	sp!,{r0-r12,lr}			;Restore registers for Angel...
	LDR		pc, Angel_SWI_Address	;if eq then branch to the Angel SWI
user_swis							;Non Angel SWI
	LDMFD	sp!, {r1-r12}			;
	BL		swi_chandler			;call C routine to handle SWI	
	LDMFD	sp!,{r0-r12,pc}^		;restore registers and return.

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
	; If it is a button interrupt, branch
	TST		r0, #0x0001		
	BNE		handler_button	
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

get_next_taskid
	CMP 	r1, #9
	BEQ		get_next_taskid_1
	ADD		r3, r1, #1			;r3 guarda o id do proximo processo
	B		get_next_taskid_2	

get_next_taskid_1
	MOV		r3, #1
	
get_next_taskid_2
	SUB		r4, r3, #1
	MOV		r5, #4
	MUL		r6, r4, r5
	LDR		r5, =Process_Table
	ADD		r5, r5, r6
	LDR		r4, [r5]
	CMP		r4, #1
	BEQ		end_get_nexttaskid
	MOV		r1, r3
	B		get_next_taskid
end_get_nexttaskid

handler_next_process
	; Verifica se o atual eh igual ao proximo
	LDR		r2, =handler_currenttaskid_str
	LDR		r2, [r2]
	CMP		r2, r3
	BEQ		handler_contextNOTswitch
		
	; Set current_task_addr to current task n
	LDR		r2, =handler_currenttaskid_str
	LDR		r2, [r2]
	MOV		r0, #68
	MUL		r1,	r2, r0
	LDR		r0, =handler_task_bottom
	ADD		r1, r1, r0
	LDR		r0, =handler_currenttaskaddr_str
	STR		r1, [r0]

	; Set next_task to point to next task
	MOV		r2, r3
	MOV		r0, #68
	MUL		r1,	r2, r0
	LDR		r0, =handler_task_bottom
	ADD		r1, r1, r0
	LDR		r0, =handler_nexttask_str
	STR		r1, [r0]
	LDR		r0, =handler_currenttaskid_str
	STR		r3, [r0]				; currrent task id = r3
	B		handler_contextswitch
	
;*********** END MARI **************

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

;********** MARI ******************	
	B		end_handler_next_process

handler_contextNOTswitch

	; Reset and save IRQ stack
	LDR		r0, =handler_irqstack_str
	MOV		r1, sp
	ADD		r1, r1, #5*4
	STR		r1, [r0]
	; Restore the remaining registers
	LDMFD		sp!,{r0-r3,lr}
	; Load the IRQ stack into r13_irq 
	LDR		r13, =handler_irqstack_str
	LDR		r13,[r13]
	; Return the next task
	;SUBS 		pc, r14, #4

end_handler_next_process
	; Return the next task
	SUBS 		pc, r14, #4
	
	
;********** END MARI ******************	



handler_button

	; C routine	
	BL	button_irq
	; Change process
	B handler_timer
	;LDMFD   sp!, {r0 - r3,lr}	 
	;SUBS    pc, lr, #4 	

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
; Stores the number of the Angel SWI
Angel_SWI_Number
	DCD	0x00123456
; Chained Angel SWI Interrupt address
Angel_SWI_Address
	DCD 	0x00000000  
; Context PCB for all the tasks (each size = 68) Offsets are from (bottom + 68 * process#)
handler_task_bottom
	% 680


;********** MARI ******************	
	
;--- Process Table ----;
	
	AREA	ProcessTable, DATA, READWRITE
	
Process_Table
	% 40
	
;********** END MARI ***************


	END