#include "gdt.h"

uint64_t stack1[STACK_SIZE];
uint64_t stack2[STACK_SIZE];
uint64_t stack3[STACK_SIZE];
uint64_t stack4[STACK_SIZE];
uint64_t stack5[STACK_SIZE];
uint64_t stack6[STACK_SIZE];
uint64_t stack7[STACK_SIZE];

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

   tss.ist[0] = (uint64_t)(&stack1[STACK_SIZE - 1]);
   tss.ist[1] = (uint64_t)(&stack2[STACK_SIZE - 1]);
   tss.ist[2] = (uint64_t)(&stack3[STACK_SIZE - 1]);
   tss.ist[3] = (uint64_t)(&stack4[STACK_SIZE - 1]);
   tss.ist[4] = (uint64_t)(&stack5[STACK_SIZE - 1]);
   tss.ist[5] = (uint64_t)(&stack6[STACK_SIZE - 1]);
   tss.ist[6] = (uint64_t)(&stack7[STACK_SIZE - 1]);

   for (int i = 0; i < 7; i++)
      printk("SP %d: %p\n", i, tss.ist[i]);

   gdtDescriptor.Size = sizeof(GDT) - 1;
   gdtDescriptor.Offset = (uint64_t)&DefaultGDT;
   LoadGDT(&gdtDescriptor);
}

