	EXPORT rotina_exec
	
	AREA	exec, CODE, READONLY

; Description: Sets up TASK B Processor Control Block
; task2[-4]  = "PCB R14" = &task2
; task2[-8]  = "PCB SP"  = TASK1 SP - 4048;
; task2[-60] = "LR"      = &task2 
; task2[-64] = "SPSR"	 = %nzcvift_User32 = 0x10
	
rotina_exec
	STMFD 	sp!,{r0-r12,lr}			;store registers
	
	MOV		pc, r1
	 
	
	;Obs: Todos os processos rodam no modo usuário.	
	
	LDMFD	sp!,{r0-r12,pc}^		;restore registers and return
	
	END