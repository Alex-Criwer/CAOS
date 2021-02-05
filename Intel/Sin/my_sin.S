	.intel_syntax noprefix
	.text
	.global my_sin

my_sin:
	mov rax, 0
	mov rsi, 0       // в rsi 0
	cvtsi2sd xmm5, rax // result
	cvtsi2sd xmm6, rax // 0.0 for cmp && flag sign
	cvtsi2sd xmm7, rax // flag
	mov rax, 1            // в rax 1
	movsd xmm2, xmm0   // x^{2k + 1}
	cvtsi2sd xmm1, rax // k = counter
	cvtsi2sd xmm3, rax // (2k + 1)!
	cvtsi2sd xmm4, rax // current_element_of_row
	
start_calculating:
	movsd  xmm4, xmm2  
	divsd  xmm4, xmm3  // curr = x^{2k + 1}/(2k + 1)!
	cvtsi2sd xmm6, rsi
	comisd xmm4, xmm6  // сравним с 0, если и сам double уже его воспринимает, как 0
	jz end_calculating

	comisd xmm7, xmm6  // прибавим или отнимем в нашей сумме, в зависимости от k
	jz my_sub
	jmp my_add
	
my_sub:
	cvtsi2sd xmm7, rax
	addsd xmm5, xmm4
	jmp next

my_add:
	cvtsi2sd xmm7, rsi
	subsd xmm5, xmm4

next: 
	cvtsi2sd xmm6, rax
	addsd xmm1, xmm6
	mulsd xmm3, xmm1 // k * (k + 1)
	addsd xmm1, xmm6
	mulsd xmm3, xmm1 // k * (k + 1) * (k + 2)
	mulsd xmm2, xmm0
	mulsd xmm2, xmm0
	jmp start_calculating

end_calculating:
	movsd xmm0, xmm5
	ret

