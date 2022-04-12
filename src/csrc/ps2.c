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

extern void ps2_poll_stat(uint16_t port, uint8_t bit)
{
   int ret = FALSE;
   int stat = 0;

   while (TRUE)
   {
      ret = inb(port);
      stat = ret;
      ret &= 0x01;
      if (ret == bit)
         break;
   }
   printk("Status : Port: %x | Status: %x\n", port, stat); 
}

extern void ps2_poll_data(uint16_t port)
{
   int ret = inb(port);
   printk("Data   : Port: %x | Status: %x\n", port, ret); 
}

extern void ps2_send_cmd(uint16_t port, uint8_t cmd)
{
   outb(port, cmd);
}
