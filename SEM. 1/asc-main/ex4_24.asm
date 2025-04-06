bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; [(a-d)+b]*2/c
    a db 4
    b db 2
    c db 8
    d db 2
    ;d db 2
    e dw 10
    f dw 12
    g dw 2
    h dw 4
; a,b,c,d-byte, e,f,g,h-word

segment code use32 class=code
    start:
        ; ...
        mov ax, 0
        mov al, [a]
        sub al, [d]
        add al, [b]
        mov bl, 2
        mul bl
        div byte [c]
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
