#include "ps2.h"

// Set to 0 to turn off messages.
#define DEBUG_MSG 0

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

extern uint8_t ps2_poll_stat(uint16_t port, uint8_t bit)
{
   int ret = FALSE;
   #if DEBUG_MSG
   int stat = 0;
   #endif

   while (TRUE)
   {
      ret = inb(port);

      #if DEBUG_MSG
      stat = ret;
      #endif

      ret &= 0x01;
      if (ret == bit)
         break;
   }
   
   #if DEBUG_MSG
   printk("Polling status...\n");
   printk("Status : Port: %x | Status: %x\n", port, stat); 
   #endif

   // To make the compiler happy (:
   return ret;
}

extern uint8_t ps2_poll_data(uint16_t port)
{
   int ret = inb(port);

   #if DEBUG_MSG
   printk("Polling data...\n");
   printk("Data   : Port: %x | Status: %x\n", port, ret); 
   #endif
   return ret;
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

extern uint8_t key_get_resp()
{
   int ret = 0;
   ret = inb(PS_DPORT);
   #if DEBUG_MSG
   printk("Keyboard response: %x\n", ret);
   #endif
   return ret;
}

extern void key_display(uint8_t code)
{
   switch(code)
   {
      case 0x02: printk("1");
         break;
      case 0x03: printk("2");
         break;
      case 0x04: printk("3");
         break;
      case 0x05: printk("4"); 
         break;
      case 0x06: printk("5");
         break;
      case 0x07: printk("6");
         break;
      case 0x08: printk("7");
         break;
      case 0x09: printk("8");
         break;
      case 0x0A: printk("9");
         break;
      case 0x0B: printk("0");
         break;
      case 0x0C: printk("-");
         break;
      case 0x0D: printk("=");
         break;
      case 0x0E: // backspace code.
         break;
      case 0x0F: // tab code.
         break;
      case 0x10: printk("q");
         break;
      case 0x11: printk("w");
         break;
      case 0x12: printk("e");
         break;
      case 0x13: printk("r");
         break;
      case 0x14: printk("t");
         break;
      case 0x15: printk("y");
         break;
      case 0x16: printk("u");
         break;
      case 0x17: printk("i");
         break;
      case 0x18: printk("o");
         break;
      case 0x19: printk("p");
         break;
      case 0x1A: printk("[");
         break;
      case 0x1B: printk("]");
         break;
      case 0x1C: printk("\n"); // enter
         break;
      case 0x1D: // left control
         break;
      case 0x1E: printk("a");
         break;
      case 0x1F: printk("s");
         break;
      case 0x20: printk("d");
         break;
      case 0x21: printk("f");
         break;
      case 0x22: printk("g");
         break;
      case 0x23: printk("h");
         break;
      case 0x24: printk("j");
         break;
      case 0x25: printk("k");
         break;
      case 0x26: printk("l");
         break;
      case 0x27: printk(";");
         break;
      case 0x28: printk("'");
         break;
      case 0x29: printk("`");
         break;
      case 0x2A: //left shift
         break;
      case 0x2B: printk("\\");
         break;
      case 0x2C: printk("z");
         break;
      case 0x2D: printk("x");
         break;
      case 0x2E: printk("c");
         break;
      case 0x2F: printk("v");
         break;
      case 0x30: printk("b");
         break;
      case 0x31: printk("n");
         break;
      case 0x32: printk("m");
         break;
      case 0x33: printk(",");
         break;
      case 0x34: printk(".");
         break;
      case 0x35: printk("/");
         break;
      case 0x36: //right shift
         break;
      case 0x37: // * keypad presss
         break;
      case 0x38: // left alt pressed
         break;
      case 0x39: printk(" ");
         break;
      default: break;
   }
}

void keyboard_init()
{
   PSContConfig k_config;
   //PSStatusReg k_stat;
   //PSOutPort k_out;
   uint8_t ps2_config = 0;

   /** TODO: KEBOARD SETUP FUNC **/
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
   k_config.p2_clk  = 0;
   k_config.p1      = 0; 
   k_config.zero2   = 0;
   
   // Collect the bits. 
   ps2_config = ps2_configure(k_config);
   // printk("PS/2 Config: %b\n", ps2_config);
   /** END NOTE **/
   
   ps2_send_data(0x60, ps2_config);

   //rintk("Verify status...\n");
   ps2_send_resp(0x20);
   
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
   //printk("Verify\n");
   ps2_poll_stat(PS_STAT, 1);
   key_get_resp();
   
   /** Set the scan code to 1**/
   ps2_poll_stat(PS_STAT, 0);
   key_send_cmd(0xF0);
   ps2_poll_stat(PS_STAT, 1);
   key_send_cmd(1);
   ps2_poll_stat(PS_STAT, 1);
   key_get_resp(); 

   /** Verify that it's keycode 1 **/
   ps2_poll_stat(PS_STAT, 0);
   key_send_cmd(0xF0);
   ps2_poll_stat(PS_STAT, 1);
   key_send_cmd(0);
   ps2_poll_stat(PS_STAT, 1);
   key_get_resp(); 

/** END TODO **/
}
