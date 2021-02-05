#include <sys/syscall.h>	
#define SIZE 4096
	.intel_syntax noprefix
	.global _start	

    .text
_start:

    push rbp
    mov rbp, rsp
    sub rsp, SIZE
    
loopBegin:
    mov rax, SYS_read
    xor rdi, rdi
    lea rsi, [rbp - SIZE]
    mov rdx, SIZE
    syscall
    
    
    push rax
    
    mov rdx, rax            // 4-ый параметр
    mov rax, SYS_write      // 1-ый параметр
    mov rdi, 1              // 2-ой параметр
    lea rsi, [rbp - SIZE]   // 3-ий параметр
    syscall
    
    pop rax
    cmp rax, SIZE
    jne loopEnd
    jmp loopBegin

loopEnd:

    add rsp, SIZE
    pop rbp 
    
    mov rax, SYS_exit
    xor rdi, rdi
    syscall
    
    

