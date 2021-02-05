	.text
	.global solve

solve:
	push {r4, r5}
	mov r4, #0
	mov r5, #0

beginLoop:
	mov r5, r0
	mul r5, r5, r4
	add r5, r5, r1
	mul r5, r5, r4
	add r5, r5, r2
	mul r5, r5, r4
	add r5, r5, r3
	cmp r5, #0
	beq endLoop
	add r4, r4, #1
	b beginLoop
endLoop:
	mov r0, r4
	pop {r4, r5}
	bx lr




