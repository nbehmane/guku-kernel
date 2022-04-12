#include "vga.h"
#include "gklib.h"
#include "ps2.h"

/** Globals **/
PSContConfig k_config;
PSStatusReg k_stat;
PSOutPort k_out;


/**** BEGIN KMAIN ****/
int kmain()
{
   printk("Welcome to Guku OS!\n");
   for (;;)
      __asm__("hlt");
   return 0;
}
/**** END KMAIN ****/
