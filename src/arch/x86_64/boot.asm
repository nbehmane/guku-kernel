; Makes a label publc.
; start is the entry point to the kernel
global start

; default section (.text) for executable code.
section .text
; 32 bit instructions
bits 32
start:
   ; print `OK` to screen.
   ; mov dword -> moves 32bit constant to memory address 0xb8000
   mov dword [0xb8000], 0x2f4b2f4f
   hlt
