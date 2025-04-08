section .data
    msg db "Hello, World. Testing strand!", 0x0A

section .text
global _start
_start:
    extern yield
    call main

main:
    mov eax, msg
    call .strlen
    mov edx, eax
    mov ecx, msg
    mov ebx, 1
    mov eax, 4
    int 0x80
    call yield

.strlen:
    push ebx
    mov ebx, eax
next_char:
    cmp  byte [eax], 0
    jz  finished
    inc eax
    jmp next_char
finished:
    sub eax, ebx
    pop ebx
    ret
