#include "gdt.h"

static uint64_t stack[STACK_SIZE];

__attribute__((aligned(0x1000)))
GDT DefaultGDT = {
   {0,0,0,0x00,0x00,0}, //NULL 0x00
   {0,0,0,0x9a,0xa0,0}, // Kernel code 0x08
   {0,0,0,0x92,0xa0,0}, //kernel data 0x10
   {0,0,0,0x00,0x00,0}, //user null 0x18
   {0,0,0,0x9a,0xa0,0}, // user code 0x20
   {0,0,0,0x92,0xa0,0}, //user data 0x28
   {0,0,0,0x89,0x00,0,0,0}, // TSS 0x30
};

void gdt_init()
{
   static GDTDescriptor gdtDescriptor;
   static TSS tss;

   DefaultGDT.TSS.limit0 = sizeof(tss);
   DefaultGDT.TSS.base0 = (((uint64_t)&tss) & 0xFFFF);
   DefaultGDT.TSS.base1 = (((uint64_t)&tss >> 16) & 0xFF);
   DefaultGDT.TSS.base2 = (((uint64_t)&tss >> 24) & 0xFF);
   DefaultGDT.TSS.base3 = (((uint64_t)&tss >> 32) & 0xFFFFFFFF);

   tss.rsp[0] = (uint64_t)(stack + (STACK_SIZE - 1));
   printk("STACK ADDR: %p\n", stack + (STACK_SIZE - 1));

   gdtDescriptor.Size = sizeof(GDT) - 1;
   gdtDescriptor.Offset = (uint64_t)&DefaultGDT;
   LoadGDT(&gdtDescriptor);
}

