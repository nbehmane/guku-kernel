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

   
   ps2_send_cmd(PS_WRITE, 0xAD);
   ps2_poll_stat(PS_STAT, 0);

   ps2_send_cmd(PS_WRITE, 0xA7);
   ps2_poll_stat(PS_STAT, 0);
   
   ps2_send_cmd(PS_WRITE, 0x20);
   ps2_poll_stat(PS_STAT, 1);
   ps2_poll_data(PS_DPORT);
   
   ps2_poll_stat(PS_STAT, 0);    // Make sure we're ready for a command.
   ps2_send_cmd(PS_WRITE, 0xAA); // send a command
   ps2_poll_stat(PS_STAT, 1); // Check to see we have something to read
   ps2_poll_data(PS_DPORT); // Read it.

   for (;;)
      __asm__("hlt");
   return 0;
}
/**** END KMAIN ****/
