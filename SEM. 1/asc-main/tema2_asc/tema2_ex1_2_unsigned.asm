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
        ; ((a + b) + (a + c) + (b + c)) - d
        mov eax, 0
        mov al, [a]
        mov bx, [b]
        add ax, bx ;a+b
        mov ebx, 0
        mov bx, [b]
        mov ecx, [c]
        add ebx, ecx ;a+c
        add eax, ebx ;(a + b) + (a + c) - eax
        mov ebx, 0
        mov bx, [b]
        add ebx, [c]
        add eax, ebx
        mov ebx, [d]
        mov ecx, [d+4]
        sub eax, ebx
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
