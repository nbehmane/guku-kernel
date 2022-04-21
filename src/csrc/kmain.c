#include "vga.h"
#include "gklib.h"
#include "ps2.h"
#include "pic.h"
#include "irq.h"

/** Helpful Macros **/
#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

/** Globals **/
PSContConfig k_config;
PSStatusReg k_stat;
PSOutPort k_out;

static uint8_t ps2_config = 0;
static uint8_t key = 0;


/**** BEGIN KMAIN ****/
int kmain()
{
   printk("Welcome to Guku OS!\n");

   // Disabling 1st port.
   ps2_poll_stat(PS_STAT, 0);
   ps2_send_cmd(PS_WRITE, 0xA7);

   // Disabling 2nd port.   
   ps2_poll_stat(PS_STAT, 0);
   ps2_send_cmd(PS_WRITE, 0xAD);

   // Getting config bits.
   ps2_send_resp(0x20);
   
   // Do a self check.
   ps2_send_resp(0xAA);

   
   /** CHECK THE USEFULLNESS OF DOING IT THIS WAY!!! **/
   // Set the configure bits for the controller.
   k_config.p1_irpt = 1;
   k_config.p2_irpt = 0;
   k_config.sf      = 1;
   k_config.zero    = 0;
   k_config.p1_clk  = 0;
   k_config.p2_clk  = 1;
   k_config.p1      = 1; 
   k_config.zero2   = 0;
   
   // Collect the bits. 
   ps2_config = ps2_configure(k_config);
   printk("PS/2 Config: %b\n", ps2_config);
   /** END NOTE **/
   
   ps2_send_data(0x60, ps2_config);

   printk("Verify status...\n");
   ps2_send_resp(0x20);
   
   // Everything was successful so clear
   VGA_clear();
   printk("Welcome to Goku OS\n");
   
   /** Reset... **/
   ps2_poll_stat(PS_STAT, 0);
   key_send_cmd(0xFF);
   ps2_poll_stat(PS_STAT, 1);
   key_send_cmd(0);
   ps2_poll_stat(PS_STAT, 1);
   key_get_resp(); 

   key_send_cmd(0xEE);
   ps2_poll_stat(PS_STAT, 1);
   key_get_resp();

   /** Check the scan code.**/
   ps2_poll_stat(PS_STAT, 0);
   key_send_cmd(0xF0);
   ps2_poll_stat(PS_STAT, 1);
   key_send_cmd(0);
   ps2_poll_stat(PS_STAT, 1);
   key_get_resp(); 

   /** Set the scan code to 1 **/
   printk("Verify\n");
   ps2_poll_stat(PS_STAT, 1);
   key_get_resp();
   
   /** Set the scan code to 1**/
   ps2_poll_stat(PS_STAT, 0);
   key_send_cmd(0xF0);
   ps2_poll_stat(PS_STAT, 1);
   key_send_cmd(2);
   ps2_poll_stat(PS_STAT, 1);
   key_get_resp(); 

   /** Verify that it's keycode 1 **/
   ps2_poll_stat(PS_STAT, 0);
   key_send_cmd(0xF0);
   ps2_poll_stat(PS_STAT, 1);
   key_send_cmd(0);
   ps2_poll_stat(PS_STAT, 1);
   key_get_resp(); 
   
   VGA_clear();
   printk("Testing printk\n");
   
   // PIC 
   PIC_init(0x20, 0x2F);
   idt_init();
   
   __asm__("int $0x0A");

   while (TRUE)
   {
      // we ready for a key code?
      ps2_poll_stat(PS_STAT, 1);
      // get that keycode bruther
      key = key_get_resp();
      // display that keycode lmao
      key_display(key);
   }
   

   for (;;)
      __asm__("hlt");
   return 0;
}
/**** END KMAIN ****/
