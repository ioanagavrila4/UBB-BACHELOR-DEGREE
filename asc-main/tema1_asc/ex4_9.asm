bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; a,b,c - byte, d - word
segment data use32 class=data
    a db 2
    b db 6
    c db 2
    d dw 50
    e equ 10
    f equ 2
    g equ 3
    h equ 20

; our code starts here
segment code use32 class=code
    start:
        ; 3*[20*(b-a+2)-10*c]+2*(d-3)
        mov al, [b]
        sub al, [a]
        add al, f
        mul h
        mov bl, al
        mov al, [c]
        mul e
        add al, bl
        mul g
        mov bl, al
        mov ax, 0
        mov ax, [d]
        sub ax, g
        mul f
        mov bh, 0
        add ax, bx
        mul g
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
