	.intel_syntax noprefix
	.text
	.global summ
summ:
	mov edi, [esp+4]  //N
	mov esi, [esp+8]  //A*
	mov edx, [esp+12] //B* 
	mov ecx, [esp+16] //R* 
	mov eax, 0 //счетчик
beginLoop:
	cmp eax, edi
	je endLoop
	mov ebx, [esi+4*eax] //temp = A[i] 
	add ebx, [edx+4*eax] //temp = A[i] + B[i]
	mov [ecx+4*eax], ebx //*R[i] = temp
	add eax, 1
	jmp beginLoop
endLoop:
	ret
	



