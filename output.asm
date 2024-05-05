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

	push rax
	push rbx
	push rdx

	mov rax, 9 
	mov rdx, 3 
	add rax, rdx
	push rax


	pop rax
	mov rdx, 8 
	imul rdx
	push rax


	pop rdx
	mov rax, 7 
	add rax, rdx
	push rax


	mov rax, 0 
	mov rdx, 9 
	add rax, rdx
	push rax


	pop rax
	pop rdx
	sub rax, rdx
	push rax


	pop rax
	mov [x0], rax

	pop rdx
	pop rbx
	pop rax

	push rax
	push rbx
	push rdx

	pop rdx
	pop rbx
	pop rax



	push r15
	mov r15, [x0]
	call _print
	pop r15

exit:
mov rax, 60
syscall