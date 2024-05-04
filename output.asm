global _start
extern _print
section .data
	f0 dq 0
	x0 dq 0
section .text
_start:
	push rax
	mov rax, 10
	mov [f0], rax
	pop rax



	push r15
	mov r15, [x0]
	call _print
	pop r15


	push r15
	mov r15, [x0]
	call _print
	pop r15

exit:
mov rax, 60
syscall