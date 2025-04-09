
section .text
global yield
yield:
    mov ebx, 0
    mov eax, 1
    int 0x80
