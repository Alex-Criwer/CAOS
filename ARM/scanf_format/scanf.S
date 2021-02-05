	.data
scanf_format:
	.string "%d%d"
printf_format:
	.string "%d\n"

	.text
	.global main
main:
	push {lr} //тк bl использует lr, то его надо запушить, чтобы не было изменений 
	//сдвинем указатель стека и запишем в регистры адреса, чтобы при scanf он записал их в стеке
	sub sp, #4
	mov r1, sp
	sub sp, #4
	mov r2, sp
	
	ldr r0, =scanf_format //передаем const char*
	bl scanf
	
	//в итоге по тем адресам записались значения, теперь их достанем
	ldr r2, [sp]
	add sp, #4
	ldr r1, [sp]
	add sp, #4

	ldr r0, =printf_format
	add r1, r2
	bl printf
	
	pop {lr}
	bx lr




