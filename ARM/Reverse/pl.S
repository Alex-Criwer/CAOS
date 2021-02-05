 .text
    .global main
main:
    push    {r4,r5,r6,lr}
    mov     r0, #10
    bl      malloc
    mov     r4, #0
    mov     r5, #10
    mov     r6, r0
    read_loop:
    bl      getchar
    cmp     r0, #-1
    beq     end_read_loop
    cmp     r4, r5
    blt     endif
    push    {r0}
    mov     r0, r6
    mov     r1, #2
    mul     r5, r1
    mov     r1, r5
    bl      realloc
    mov     r6, r0
    pop     {r0}
    endif:
    strb    r0, [r6, r4]
    add     r4, #1
    b       read_loop
    end_read_loop:
    write_loop:
    sub     r4, #1
    cmp     r4, #-1
    beq     end_write_loop
    ldrb    r0, [r6, r4]
    bl      putchar
    b       write_loop
    end_write_loop:
    mov     r0, r6
    bl      free
    mov     r0, #0
    pop     {r4,r5,r6,pc}
