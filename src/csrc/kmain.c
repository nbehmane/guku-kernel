#include "vga.h"

/**** BEGIN KMAIN ****/
int kmain()
{
   VGA_display_str(0, 0, "Hello, world!", 0); 
   for (;;)
      __asm__("hlt");
   return 0;
}
