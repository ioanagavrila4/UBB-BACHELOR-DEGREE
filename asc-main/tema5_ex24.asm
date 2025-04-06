bits 32 ; assembling for the 32 bits architecture

;se dau 2 siruri de octeti A si B. Sa se construiasca sirul R care sa contina elementele lui B in ordine inversa urmate de elementele in ordine inversa ale lui A.
;Exemplu:
;A: 2, 1, -3, 0
;B: 4, 5, 7, 6, 2, 1
;R: 1, 2, 6, 7, 5, 4, 0, -3, 1, 2
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    a db 2, 1, -3, 0
    lungime equ $-a
    b db 4, 5, 7, 6, 2, 1
    l equ ($-b)
    r times lungime+l db 0
    

; our code starts here
segment code use32 class=code
    start:
        mov ecx, l
        mov esi, l
        mov edi, 0
        dec esi
        jecxz Sfarsit ;aici se verifica doar daca continutul din ecx e 0
        Repeta:
            mov al, [b+esi]
            
            mov[r+edi], al ;punem la pozitia corespunzatoare din d rezultatul
            inc edi
            dec esi
        loop Repeta
        Sfarsit:
        mov ecx, lungime
        mov esi, lungime
        dec esi
        jecxz SfarsitA ;aici se verifica doar daca continutul din ecx e 0
        RepetaA:
            mov al, [a+esi]
            mov[r+edi], al ;punem la pozitia corespunzatoare din d rezultatul
            inc edi 
            dec esi
        loop RepetaA
        SfarsitA:
        
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
