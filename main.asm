section .data
    buffer dd 32
    msg_01 db "Welcome to Seedling!", 0x0A, 0x00
    msg_02 db "Its getting there!", 0x0A, 0x00

section .text
global _start
_start:
    extern yield
    extern write
    call main

main:
    mov dword [buffer], 32
    mov eax, msg_01
    call write
    mov eax, msg_02
    call write
    call yield
