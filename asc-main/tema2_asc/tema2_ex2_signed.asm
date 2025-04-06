bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    a db -3
    b db -2
    c dw 5
    e dd 10
    x dq 130

; our code starts here
segment code use32 class=code
start:
    ;(a-b+c*128)/(a+b)+e-x; a,b-byte; c-word; e-doubleword; x-qword
    mov al, [a]
    sub al, [b]
    cbw
    mov bx, ax
    mov ax, [c]
    mov cx, 128
    imul cx
    add ax, bx ;a-b+c*128 in ax
    mov cx, ax
    mov eax, 0
    mov al, [a]
    add al, [b]
    cbw
    mov bx, ax
    mov ax, cx
    idiv bx
    cwd
    add eax, [e]
    cdq
    sub eax, [x]
    sbb edx, [x+4]
    
    ; exit(0)
    push dword 0         ; push the parameter for exit onto the stack
    call [exit]            ; call exit to terminate the program


