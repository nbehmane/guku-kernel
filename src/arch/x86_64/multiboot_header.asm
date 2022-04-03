section .multiboot_header
header_start:
   ; dd -> define double -> outputs 32bit constant
   dd 0xe85250d6                ; magic number (multiboot 2)
   dd 0                         ; architexture 0 (protected mode i386)
   dd header_end - header_start ;
   ; checksum
   dd 0x100000000 - (0xe85250d6 + 0 + (header_end - header_start))
   
   ; Optional Boot Flags
   
   ; Required end tag
   ; dw -> define word -> outputs 16bit constant
   dw 0 ; type
   dw 0 ; flags
   dd 8 ; size
header_end:
