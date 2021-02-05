	.text
	.global summ 

summ:
	loopBegin:
		cmp r1, #0
		beq loopEnd
		sub r1, r1, #1
		ldr r3, [r2]
		add r2, r2, #4
		add r0, r0, r3
        b loopBegin
	loopEnd:
		mov r1, r0
		bx lr


