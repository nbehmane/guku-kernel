#include "ps2.h"

void set_stat(PSStatusReg *reg)
{
   reg->o_buff = 0;
   reg->i_buff = 0;
   reg->cmd_data = 1;
}

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
