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
   outb(PS_WRITE, 32);
   wait();
   ret = inb(PS_DPORT);
   wait();
   print_int(ret);
   
   for (;;)
      __asm__("hlt");
   return 0;
}
/**** END KMAIN ****/
