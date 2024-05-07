global _start
extern _print
section .data
	i0 dq 0
	x0 dq 0
	y0 dq 0
section .text
_start:
	push rax
	mov rax, 456
	mov [x0], rax
	pop rax

	push rax
	mov rax, 3
	mov [i0], rax
	pop rax

	push rax
	push rbx
	push rdx

	mov rax, [x0] 
	mov rdx, 2 
	mov rbx, rdx
	xor rdx, rdx
	idiv rbx
	push rax


	pop rax
	mov [y0], rax

	pop rdx
	pop rbx
	pop rax

	push rax
	push rbx
	push rdx

	while0:
		mov rax, [x0] 
	mov rdx, 2 
	mov rbx, rdx
	xor rdx, rdx
	idiv rbx
	push rdx


	pop rax
	mov rdx, 0 
	cmp rax, rdx
	je true0
	push 0
	jmp end0
	true0:
		push 1
	end0:
	pop rax
	cmp rax,1
	jne end_loop0

	pop rdx
	pop rbx
	pop rax



	push r15
	mov r15, 2
	call _print
	pop r15
	push rax
	push rbx
	push rdx

	mov rax, [x0] 
	mov rdx, 2 
	mov rbx, rdx
	xor rdx, rdx
	idiv rbx
	push rax


	pop rax
	mov [x0], rax

	pop rdx
	pop rbx
	pop rax

	jmp while0
	end_loop0:

	push rax
	push rbx
	push rdx

	while1:
		mov rax, [i0] 
	mov rdx, [y0] 
	cmp rax, rdx
	jl true1
	push 0
	jmp end1
	true1:
		push 1
	end1:
	pop rax
	cmp rax,1
	jne end_loop1

	pop rdx
	pop rbx
	pop rax

	push rax
	push rbx
	push rdx

	while2:
		mov rax, [x0] 
	mov rdx, [i0] 
	mov rbx, rdx
	xor rdx, rdx
	idiv rbx
	push rdx


	pop rax
	mov rdx, 0 
	cmp rax, rdx
	je true2
	push 0
	jmp end2
	true2:
		push 1
	end2:
	pop rax
	cmp rax,1
	jne end_loop2

	pop rdx
	pop rbx
	pop rax



	push r15
	mov r15, [i0]
	call _print
	pop r15
	push rax
	push rbx
	push rdx

	mov rax, [x0] 
	mov rdx, [i0] 
	mov rbx, rdx
	xor rdx, rdx
	idiv rbx
	push rax


	pop rax
	mov [x0], rax

	pop rdx
	pop rbx
	pop rax

	jmp while2
	end_loop2:

	push rax
	push rbx
	push rdx

	mov rax, [i0] 
	mov rdx, 2 
	add rax, rdx
	push rax


	pop rax
	mov [i0], rax

	pop rdx
	pop rbx
	pop rax

	jmp while1
	end_loop1:


exit:
mov rax, 60
syscall