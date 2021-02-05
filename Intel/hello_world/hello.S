#include <sys/syscall.h>	
	.intel_syntax noprefix
	.global _start
	.data
hello_world: 
    .string "Hello, World!\n"
    
    .text
_start:
	mov rax, SYS_write
	mov rdi, 1
	mov rsi, offset hello_world
	mov rdx, 14
	syscall
	mov rax, SYS_exit
	syscall
	
	


