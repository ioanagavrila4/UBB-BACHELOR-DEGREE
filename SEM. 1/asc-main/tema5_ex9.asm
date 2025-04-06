bits 32 ; assembling for the 32 bits architecture

;Se da un sir de octeti S de lungime l. Sa se construiasca sirul D de lungime l-1 astfel incat elementele din D sa reprezinte diferenta dintre fiecare 2 elemente consecutive din S.
;Exemplu:
;S: 1, 2, 4, 6, 10, 20, 25
;D: 1, 2, 2, 4, 10, 5
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    s db 1, 2, 4, 6, 10, 20, 25 ; stocare sir s
    l equ $-s ; lungimea lui s
    d times l-1 db 0 ;noul sir d

; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov ecx, l - 1 ;contor pt loop
        mov esi, 0
        mov edi, 0
        jecxz Sfarsit ;aici se verifica doar daca continutul din ecx e 0
        Repeta:
            mov al, [s+esi]
            inc esi
            mov bl, [s+esi]
            sub bl, al
            
            mov[d+edi], bl ;punem la pozitia corespunzatoare din d rezultatul
            inc edi
            
        loop Repeta
        Sfarsit:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
