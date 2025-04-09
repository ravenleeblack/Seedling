
section .text
global write
write:
    push edx
    push ecx
    push ebx
    push eax
    call .strand
    mov edx, eax
    pop eax
    mov ecx, eax
    mov ebx, 1
    mov eax, 4
    int 0x80
    pop ebx
    pop ecx
    pop edx
    ret

.strand:
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
