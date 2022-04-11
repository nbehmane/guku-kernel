#include "vga.h"
#include "gklib.h"

/**** BEGIN KMAIN ****/
int kmain()
{
   for (;;)
      __asm__("hlt");
   return 0;
}
