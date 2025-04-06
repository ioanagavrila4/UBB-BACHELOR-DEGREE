bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 5
    b dw 10
    c dd 15
    d dq 100
    

; a - byte, b - word, c - double word, d - qword - Unsigned representation

segment code use32 class=code
    start:
        ; (d+d-b)+(c-a)+d
        mov eax, [d]
        mov edx, [d+4]
        mov ebx, [d]
        mov ecx, [d+4]
        add eax, ebx
        adc edx, ecx
        mov ecx, 0
        mov cx, [b]
        sub eax, ecx
        sbb edx, 0
        mov ecx, 0
        mov ecx, [c]
        mov ebx, 0
        mov bl, [a]
        sub ecx, ebx
        add eax, ecx
        adc edx, 0
        mov ebx, [d]
        mov ecx, [d+4]
        add eax, ebx
        adc edx, ecx
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
