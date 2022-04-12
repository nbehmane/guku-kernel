#include "ps2.h"

// Set to 0 to turn off messages.
#define DEBUG_MSG 1

extern uint8_t inb(uint16_t port)
{
   uint8_t ret;
   asm volatile ("inb %1, %0;" :"=a"(ret) :"Nd"(port));
   return ret;
}

extern void outb(uint16_t port, uint8_t val) 
{
   asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port));
}

extern void ps2_poll_stat(uint16_t port)
{
   int ret = FALSE;

   #if DEBUG_MSG
   int stat = 0;
   printk("Polling status.\n");
   #endif

   while (ret == FALSE)
   {
      ret = inb(port);

      #if DEBUG_MSG
      stat = ret;
      #endif

      ret |= 0xFE;
   }
   #if DEBUG_MSG
   printk("Status: %x\n", stat); 
   #endif
}

extern void ps2_send_cmd(uint16_t port, uint16_t port2, uint8_t cmd)
{
   ps2_poll_stat(port2);

   #if DEBUG_MSG  
   printk("Sending command...\n");
   #endif

   outb(port, cmd);
   
   #if DEBUG_MSG
   printk("%x command sent.\n", cmd);
   #endif
}
