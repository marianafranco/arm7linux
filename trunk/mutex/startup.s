; Startup assembly code
; Obs.: This code was built supposing that the generated assembly is ARM
; assembly, not THUMB!!!
	
	IMPORT	current_thread_id
	IMPORT	thread_array
	IMPORT 	C_Entry

	; Identifying that from below on it is assembly code (readable only)
	AREA asm_init, CODE
	
	; Entry point of the program
	ENTRY
|start|

	; Beginning assembly initialization

	; Changing to IRQ mode and disabling interruptions, then setting up 
	; IRQ stack pointer to 0x8000
	MOV		r0,	#0xC0|0x12		; r0 = 0xC0 or 0x12 (0xC0 = IRQ disabled, 
								; 0x12 = IRQ mode)
	MSR		CPSR_c, r0			; status_register = r0
	MOV		sp, #0x8000			; stack pointer = 0x8000
	
	; Changing to system mode and disabling interruptions, then setting up 
	; user stack pointer to 0x20000
	MOV		r0, #0xC0|0x1F		; r0 = 0xC0 or 0x1F (0xC0 = IRQ disabled,
								; 0x1F = system mode)
	MSR		CPSR_c, r0			; status_register = r0
	MOV		sp, #0x20000		; stack pointer = 0x20000
	
	; Changing to SVC mode and disabling interruptions, then setting up 
	; SVC stack pointer to 0x8000 - 128
	MOV		r0,	#0xC0|0x13		; r0 = 0xC0 or 0x13 (0xC0 = IRQ disabled,
								; 0x13 = SVC mode)
	MSR		CPSR_c, r0			; status_register = r0
	MOV		r0, #0x8000			; r0 = 0x8000
	SUB		r0, r0, #128		; r0 = r0 - 128
	MOV		sp, r0				; stack pointer = r0
	
	; Initializes the thread array with zeros (0 = thread disabled, 
	; 1 = thread enabled)
	LDR		r0, =thread_array		; r0 = thread_array start address
	MOV		r1, #1					; r1 = 1
	STR		r1, [r0]				; address(r0) = r1
	MOV		r1, #0					; r1 = 0
	MOV		r2, #0					; r2 = 0
init_thread_array_loop
	ADD		r2, r2, #4				; r2 = r2 + 4 
	CMP		r2, #36					; r2 = 36?
	BEQ		set_active_thread		; if yes, go to set_active_thread
	ADD		r3, r0, r2				; r3 = r0 + r2
	STR		r1, [r3]				; address(r3) = r1
	B		init_thread_array_loop	; return to init_thread_array_2

	; Setting the thread id to 1
set_active_thread
	LDR		r0, =current_thread_id
	MOV		r1, #1
	STR		r1, [r0]

	; Pass control to C_Entry
	LDR 	lr, =C_Entry
	MOV 	pc, lr

	; End of assembly code
	END