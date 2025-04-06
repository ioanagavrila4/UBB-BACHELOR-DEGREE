bits 32 ; assembling for the 32 bits architecture

global start
extern operation_function

; declare external functions needed by our program
extern exit, scanf, printf
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    format db "%d", 0          
    output_format db "%d", 10, 0  
    a dd 0
    b dd 0
    c dd 0
    rezultat dd 0              ; Variabila pentru rezultat

segment code use32 class=code
start:
    ; Citire a
    push dword a
    push dword format
    call [scanf]
    add esp, 4*2            

    ; Citire b
    push dword b
    push dword format
    call [scanf]
    add esp, 4*2             

    ; Citire c
    push dword c
    push dword format
    call [scanf]
    add esp, 4*2              

    
    mov ebx, [a]               ; a în ebx
    mov ecx, [b]               ; b în ecx
    mov edx, [c]               ; c în edx

    call operation_function    ; Apel funcție pentru a+b-c

    mov [rezultat], ebx        ; Salvează rezultatul în memorie

    
    push dword [rezultat]
    push dword output_format
    call [printf]
    add esp, 8              

    ; Terminare program
    push dword 0
    call [exit]