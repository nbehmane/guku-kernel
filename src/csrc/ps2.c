#include "ps2.h"

// Set to 0 to turn off messages.
#define DEBUG_MSG 1

/** Internal Functions **/


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
   
   #if DEBUG_MSG
   printk("Polling status...\n");
   printk("Status : Port: %x | Status: %x\n", port, stat); 
   #endif
}

extern void ps2_poll_data(uint16_t port)
{
   int ret = inb(port);

   #if DEBUG_MSG
   printk("Polling data...\n");
   printk("Data   : Port: %x | Status: %x\n", port, ret); 
   #endif
}

extern void ps2_send_cmd(uint16_t port, uint8_t cmd)
{
   outb(port, cmd);
}

extern void ps2_send_resp(uint8_t cmd)
{
   ps2_poll_stat(PS_STAT, 0);
   #if DEBUG_MSG
   printk("Sending cmd %x\n", cmd);
   #endif
   ps2_send_cmd(PS_WRITE, cmd);
   #if DEBUG_MSG
   printk("Waiting for response...\n");
   #endif
   ps2_poll_stat(PS_STAT, 1);
   ps2_poll_data(PS_DPORT);
}

extern void ps2_send_data(uint8_t cmd, uint8_t data)
{
   ps2_poll_stat(PS_STAT, 0);    // Make sure we're ready for a command.
   #if DEBUG_MSG
   printk("Sending cmd %x\n", cmd);
   #endif
   ps2_send_cmd(PS_WRITE, cmd); // send a command
   ps2_poll_stat(PS_STAT, 0); // Make sure we're ready to send something 
   #if DEBUG_MSG
   printk("Sending data %x\n", data);
   #endif
   ps2_send_cmd(PS_DPORT, data); // send the config.
}

extern uint8_t ps2_configure(PSContConfig conf)
{
   uint8_t config_bits = 0;
   config_bits |= conf.p1_irpt;
   config_bits |= conf.p2_irpt << 1;
   config_bits |= conf.sf << 2;
   config_bits |= conf.zero << 3;
   config_bits |= conf.p1_clk << 4;   
   config_bits |= conf.p2_clk << 5;
   config_bits |= conf.p1 << 6;
   config_bits |= conf.zero2 << 7;

   return config_bits;
}

extern void key_send_cmd(uint8_t cmd)
{
   outb(PS_DPORT, cmd);
}

extern void key_get_resp()
{
   int ret = 0;
   ret = inb(PS_DPORT);
   printk("Keyboard response: %x\n", ret);
}






