	.text
	.global main

main:
	push {r4-r7, lr} //будем хранить так: r4 = heap_pointer, r5 = bufferSize, r6 = capacitySize
	mov r4, #0
	mov r5, #0
	mov r6, #0

read:
	bl getchar
	mov r7, r0
	cmp r0, #-1   //если EOF, то закончили считывать символы
	beq whrite 
	cmp r5, r6 //если size > capacity, то realloc
	blt withoutReallocating
	add r6, #10 //увеличиваем capacity
	mov r0, r4
	mov r1, r6
	bl realloc 
	mov r4, r0  //перемещаем новый адрес обратно в r4

		
withoutReallocating:
	add r0, r4, r5
	strb r7, [r0]
	add r5, #1
	b read

whrite:
	cmp r5, #0
	beq endProgramm 
	add r0, r4, r5
	sub r0, #1
	ldrb r0, [r0]	
	bl putchar
	sub r5, #1
	b whrite
	

endProgramm:
	mov r0, r4 //перемещаем указатель, чтобы его отчистить
	bl free
	pop {r4-r7, lr}
	bx lr
 
