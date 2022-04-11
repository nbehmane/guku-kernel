#include "vga.h"
#include "gklib.h"
#include "ps2.h"

/**** BEGIN KMAIN ****/
int kmain()
{
   long num = 1983274;
   print_long_hex(num);
   for (;;)
      __asm__("hlt");
   return 0;
}
