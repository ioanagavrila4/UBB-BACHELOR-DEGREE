bits 32               ; assembling for the 32-bit architecture
global start          ; define the entry point

extern exit           ; declare external exit function
import exit msvcrt.dll

segment data use32 class=data
    a dw 0001001000110100b       ; declare `a` as a word (16-bit)
    b db 10101011b           ; declare `b` as a byte (8-bit)
    c dd 0            ; declare `c` as a doubleword (32-bit)

segment code use32 class=code
    start:
        mov eax, 0           
        mov ebx, 0        

      
        mov ax, [a]        
        and ax, 0x03C0       
        shr ax, 6          
        mov ebx, eax        
 
        or ebx, 0x30         

        mov al, [b]          
        and al, 0x06          
        shl al, 5           
        or bl, al            

        mov eax, [a]        
        shl eax, 8       
        or ebx, eax      

        mov eax, [b]      
        shl eax, 24          
        or ebx, eax          
        ;mov [c], ebx  

        ; Exit program with code 0
        push dword 0          ; Push 0 as the exit code
        call [exit]           ; Call exit to terminate the program
