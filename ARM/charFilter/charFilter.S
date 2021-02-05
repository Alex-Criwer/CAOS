	.text
	.global main

main:
	push {lr} //запишем lr в стэк, т.к. bl его использует и может изменить 

loopBegin: 
	bl getchar //принимает void
	cmp r0, #-1
	beq loopEnd
	cmp r0, #'0'
	blt loopBegin
	cmp r0, #'9'
	bgt loopBegin
	bl putchar
	b loopBegin 
loopEnd:
	pop {lr}
	bx lr

