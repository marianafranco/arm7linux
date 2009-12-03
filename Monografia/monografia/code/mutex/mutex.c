unsigned volatile int semaphore	= 2; // this is a start value
	
void mutex_gatelock (void) {
	__asm {
		spin:
		mov		r1, &semaphore
		mov		r2, #1
		swp		r3,r2,[r1]
		cmp		r3,#1
		beq		spin
	}
}

void mutex_gateunlock (void)  {
	__asm  {
		mov		r1, &semaphore
		mov		r2, #0
		swp		r0,r2,[r1]
	}
}