global _start
extern _print
section .data
	x0 dq 0
section .text
_start:
	push rax
	push rbx
	push rdx

	mov rax, 0 
	mov rdx, 567 
	add rax, rdx
	push rax


	pop rax
	mov rdx, 246 
	imul rdx
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