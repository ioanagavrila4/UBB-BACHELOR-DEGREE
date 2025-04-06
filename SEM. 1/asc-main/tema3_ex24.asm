bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; Se da dublucuvantul M. Sa se obtina dublucuvantul MNew astfel:
;bitii 0-3 a lui MNew sunt identici cu bitii 5-8 a lui M
;bitii 4-7 a lui MNmov ebx,ew au valoarea 1
;bitii 27-31 a lui MNew au valoarea 0
;bitii 8-26 din MNew sunt identici cu bitii 8-26 a lui M.
segment data use32 class=data
    ; ...
    m dd 10101100010101011111000000001111b
    mnew dd

; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov eax, 0 ;aici o sa punem noul cuvant
        mov ebx, 0
        mov ebx, [m]
        shl ebx, 5
        and ebx, 000000000000000000000000000001111b
        or eax, ebx
        mov ebx, 00000000000000000000000011110000b
        or eax, ebx
        mov ebx, 11111000000000000000000000000000b
        or eax, ebx
        mov ebx, [m]
        and ebx, 00000111111111111111111100000000b
        or eax, ebx
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
