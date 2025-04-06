bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; Se da un sir de dublucuvinte. Sa se obtina, incepand cu partea inferioara a dublucuvantului, dublucuvantul format din octetii
; superiori pari ai cuvintelor inferioare din elementele sirului de dublucuvinte. Daca nu sunt indeajuns octeti
; se va completa cu octetul FFh.

segment data use32 class=data
    s dd 12345678h, 1A2C3C4Dh, 98FCDD76h, 12783A2Bh ; Input doublewords
    len equ ($-s)/4         ; Number of doublewords in 's'
    rezultat dd 0           ; for the final result

segment code use32 class=code
start:
    mov esi, s               ; Load address of 's' into esi
    xor ebx, ebx             ; Clear ebx
    xor edx, edx             ; Counter for added bytes (max 4?)
    mov ecx, len             ; Set loop counter (number of doublewords)

parcurgere:
    lodsd                    ; Load one doubleword from 's' into eax
    and ax, 0xFF00           ; Mask to extract the upper byte of the lower word
    shr ax, 8                ; Shift to position the upper byte in AL
    mov dl, al               ; Move the extracted byte into DL

    ; Check if the byte is even
    test dl, 1               ; Check the least significant bit of the byte
    jnz next_word            ; If odd, skip to the next word

    ; Add the byte to the result
    shl ebx, 8               ; Shift the result left to make space for the new byte
    or bl, dl                ; Add the byte to the result
    inc edx                  ; Increment the counter for added bytes
    cmp edx, 4               ; Check if we've added 4 bytes
    je finalize              ; If yes, skip the rest

next_word:
    dec ecx                  ; Decrement the loop counter
    jnz parcurgere           ; Continue if there are more doublewords

    ; Fill the rest of the result with 0xFF if fewer than 4 bytes were added
    cmp edx, 4               ; Check if fewer than 4 bytes are added
    je finalize              ; Skip padding if already complete
completare:
    cmp edx, 4               ; Check if we've added 4 bytes
    je finalize 
    shl ebx, 8               ; Shift left to make space for the padding byte
    or bl, 0xFF              ; Add 0xFF
    inc edx                  ; Increment the counter
    cmp edx, 4               ; Check if we've added 4 bytes
    je finalize          ; Repeat if not done

finalize:
    mov [rezultat], ebx      ; Store the final result in 'rezultat'

    ; Exit the program
    push 0                   ; Exit code 0
    call [exit]              ; Call the exit function
