bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; a - byte, b - word, c - double word, d - qword - Signed representation
    a db -5
    b dw 10
    c dd 15
    d dq 100
    

; our code starts here
segment code use32 class=code
    start:
        ; a-d+b+b+c
        
        mov al, [a]
        cbw
        cwd
        cwde
        cdq ; a se afla pe edx:eax
        mov ebx, [d]
        mov ecx, [d+4]
        sub eax, ebx
        sbb edx, ecx ; a-d pe edx:eax
        mov ecx, edx
        mov ebx, eax
        mov ax, [b]
        cwd 
        cwde 
        cdq
        add ebx, eax
        adc ecx, edx
        add ebx, eax
        adc ecx, edx
        mov eax, [c]
        cdq
        add ebx, eax
        adc ecx, edx
        
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
