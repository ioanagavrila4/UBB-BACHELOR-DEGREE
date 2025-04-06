bits 32
global start
extern exit
import exit msvcrt.dll
segment data use32 class=data
    sir dd 0x1, 0x3, 0x1, 0x7, 0x9, 0xA ; Input array of doublewords
    len equ ($-sir)/4                  ; Number of elements in the array
    rezultat dd 0, 0, 0, 0, 0, 0       ; Space for results

segment code use32 class=code
start:
    mov esi, sir         ; Load the address of the input array
    mov edi, rezultat    ; Load the address of the result array
    mov ecx, len         ; Set the loop counter to the number of elements

repeta:
    lodsd                
    push eax             ; Save eax (the current doubleword)

    xor ebx, ebx         ; ebx - counter of 1 s
parity:
    shr eax, 1           ; Shift right to check the next bit
    adc ebx, 0           ; Add the carry flag to the counter
    test eax, eax        ; the condition for stopping the loop
    jnz parity           ; Repeat until all bits are processed

    test ebx, 1          ; Check if the number of 1 bits is odd
    jnz next_element     ; If odd, skip saving this doubleword

mutare:
    pop eax              ; Restore the original value of eax
    mov [edi], eax       ; Store the value in the result array
    add edi, 4           ; Move the result pointer forward

next_element:
    pop eax              ; Restore eax if it was not restored earlier
    loop repeta          ; Decrement ecx and repeat if not zero

    ; End of program
    push dword 0         ; Push exit code 0
    call [exit]          ; Call the exit function
