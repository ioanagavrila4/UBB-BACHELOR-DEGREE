bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global operation_function      


segment code use32 public code
    operation_function:
        add ebx, ecx
        sub ebx, edx
        ret