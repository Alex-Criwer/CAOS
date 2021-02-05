    .intel_syntax noprefix
    .global dot_product
    
    .text
    
dot_product:
    //в rdi N, rsi - *A, rdx - *B 
    xorps xmm0, xmm0
    xor rax, rax
    mov rcx, rdi                 // кладем туда копию, чтобы округлить до 4-ых
    sar rcx, 2
    sal rcx, 2                   // округляем до числа, делящегося на 4
loopBegin:
    cmp rax, rcx
    je loopEnd
    movups xmm1, [rsi + 4*rax]   // movups, т.к. не гарант. выравнивания
    movups xmm2, [rdx + 4*rax]   // 4, т.к. у float 4 байта
                                 // xmm1 = (a1, a2, a3, a4), xmm2 = (b1, b2, b3, b4)
    mulps xmm1, xmm2             // after mulps: xmm1 = (a1*b1, a2*b2, a3*b3, a4*b4)

    haddps xmm1, xmm1            // xmm1 = (a1*b1 + a2*b2, a3*b3 + a4*b4, a1*b1 + a2*b2, a3*b3 + a4*b4)
    haddps xmm1, xmm1            // xmm1 = (..., a1*b1 + a2*b2 + a3*b3 + a4*b4)
    
    addss xmm0, xmm1
    add rax, 4
    jmp loopBegin
loopEnd:
loopTheRest:
    cmp rax, rdi
    je loopEndTheRest
    movups xmm1, [rsi + 4*rax]   
    movups xmm2, [rdx + 4*rax]
    mulps   xmm1, xmm2
    addss   xmm0, xmm1
    inc rax
    jmp loopTheRest 
    
loopEndTheRest:
    ret
