global _start
extern _print
section .data
	x0 dq 0
section .text
_start:
	push rax
	mov rax, 0
	mov [x0], rax
	pop rax

	push rax
	push rbx
	push rdx

	pop rax
	mov [while0], rax

	pop rdx
	pop rbx
	pop rax



	push r15
	mov r15, [x0]
	call _print
	pop r15
	push rax
	push rbx
	push rdx

	mov rax, [x0] 
	mov rdx, 1 
	add rax, rdx
	push rax


	pop rax
	mov [x0], rax

	pop rdx
	pop rbx
	pop rax


exit:
mov rax, 60
syscall