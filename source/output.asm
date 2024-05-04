global _start
extern _print
section .data
section .text
_start:

exit:
mov rax, 60
syscall