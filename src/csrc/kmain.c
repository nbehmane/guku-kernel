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
   ps2_send_cmd(PS_WRITE, PS_DPORT, 0xAA);
   ps2_poll_stat(PS_DPORT);
   for (;;)
      __asm__("hlt");
   return 0;
}
/**** END KMAIN ****/
