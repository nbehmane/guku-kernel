#include "vga.h"
#include "gklib.h"
#include "ps2.h"

/** Globals **/
PSContConfig k_config;
PSStatusReg k_stat;
PSOutPort k_out;

/** kmain Internal Funcs **/
void wait()
{
   int i = 0;
   int max = 1000;
   for (i = 0; i < max; i++);
}

/**** BEGIN KMAIN ****/
int kmain()
{
   uint8_t ret = 0;
   // Testing PS/2 Controller
   // Disable first port
   outb(PS_WRITE, 0xAD);
   wait();
   ret = inb(PS_DPORT);
   print_long_hex(ret);

   // Testing PS/2 Controller
   outb(PS_WRITE, 0xAA);
   wait();
   ret = inb(PS_DPORT);
   print_long_hex(ret);

   // Testing PS/2 Port
   outb(PS_WRITE, 0xAB);
   wait();
   ret = inb(PS_DPORT);
   print_long_hex(ret);
   
   for (;;)
      __asm__("hlt");
   return 0;
}
/**** END KMAIN ****/
