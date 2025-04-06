bits 32

global start

extern exit
import exit msvcrt.dll

segment data use32 class = data
    a dd 100
    b db 8
    c db 36
    d db 1
    x dq 61

segment code use32 class =  code
start:
    ; a-(7+x)/(b*b-c/d+2); a-doubleword; b,c,d-byte; x-qword
    ; 7 + x
    mov eax, [x]
    mov edx, [x+4]
    add eax, 7
    adc edx, 0
    mov ebx, eax
    mov ecx, edx
    
    ; b*b-c/d in dx
    
    mov al, [b]
    imul byte [b]
    cbw
    mov dx, ax
    
    ;c/d
    mov ax, 0
    mov al, [c]
    idiv byte [d] ; al = 36
    
    sub dx, ax
    mov al, 2
    cbw
    add dx, ax
    
    ; in eax se afla b*b-c/d+2
    mov ax, dx
    cwd
    mov edx, eax
    mov eax, ebx
    mov ebx, edx
    mov edx, ecx
    idiv ebx
    mov ebx, eax
    mov ecx, edx
    mov eax, [a]
    cdq
    sub eax, ebx
    sbb edx, ecx
    
    push dword 0
    call [exit]