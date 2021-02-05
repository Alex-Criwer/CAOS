	.data
	.word A
	.word B
	.word C
	.word D
	.global R
R:	.space 4

	.text 
	.global calculate
	
calculate:
	push {r4}     // пусть r0 = R, r1 = A, r2 = B, r3 = C, r4 = D
	ldr r1, =A
	ldr r1,[r1]
	
	ldr r2, =B
	ldr r2, [r2]

	ldr r3, =C
	ldr r3, [r3]

	ldr r4, =D
	ldr r4, [r4]

	mul r1, r2  //A * B
	mul r3, r4  //C * D
	add r0, r1, r3

	ldr r1, =R
	str r0, [r1] 

	pop {r4}
	bx lr





