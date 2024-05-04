global _start
extern _print
section .data
	c0 dq 0
	x0 dq 0
section .text
_start:
	push rax
	mov rax, 0
	mov [x0], rax
	pop rax

	push rax
	mov rax, 9
	mov [c0], rax
	pop rax

	push rax
	push rbx
	push rdx

	mov rax, 4 
	mov rdx, 4 
	add rax, rdx
	push rax


	mov rax, 7 
	mov rdx, 9 
	imul rdx
	push rax


	pop rax
	pop rdx
	imul rdx
	push rax


	mov rax, 0 
	mov rdx, [x0] 
	sub rax, rdx
	push rax


	pop rdx
	mov rax, 9 
	sub rax, rdx
	push rax


	pop rax
	pop rdx
	add rax, rdx
	push rax


	mov rax, [c0] 
	mov rdx, 8 
	imul rdx
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



	push r15
	mov r15, [x0]
	call _print
	pop r15

exit:
mov rax, 60
syscall