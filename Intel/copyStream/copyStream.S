	#include <sys/syscall.h>	
	.intel_syntax noprefix
	.global _start
	.data 
SIZE dq 10000
    .text
_start:
	mov rax, SYS_exit
	xor rdx, rdx
	syscall





