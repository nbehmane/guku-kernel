[bits 64]
LoadGDT:
   lgdt [rdi]
   mov ax, 0x10
   mov ds, ax
   mov es, ax
   mov fs, ax
   mov gs, ax
   mov ss, ax
   pop rdi 
   mov rax, 0x08
   push rax
   push rdi
   mov ax, 0x30
   ltr ax
   retfq

global LoadGDT
