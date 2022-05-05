#include "irq.h"
#include "vga.h"
#include "pic.h"

__attribute__((aligned(0x10))) static idt_entry_t idt[256];
static idtr_t idtr;
extern void* isr_stub_table[];

void exception_handler(uint8_t intrpt) 
{
   register void *sp asm ("sp");
   int i = 0;
   printk("-------------------\n");
   printk("Current SP     : %p\n", sp);
   printk("Interrupt      : %d\n", intrpt);
   printk("Interrupt Addr : %d\n", &intrpt);
   printk("Local Var Addr : %p\n", &i);
   printk("-------------------\n");
   PIC_sendEOI(intrpt - 0x20);
}

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags, int ist) {
    idt_entry_t* descriptor = &idt[vector];
 
    descriptor->isr_low       = (uint64_t)isr & 0xFFFF;
    descriptor->kernel_cs     = GDT_OFFSET_KERNEL_CODE;
    descriptor->ist           = ist; // Set to 1 since we want to use the first IST
    descriptor->attributes    = flags;
    descriptor->isr_mid       = ((uint64_t)isr >> 16) & 0xFFFF;
    descriptor->isr_high      = ((uint64_t)isr >> 32) & 0xFFFFFFFF;
    descriptor->reserved      = 0;
}

void idt_init(void) {
    idtr.base = (uintptr_t)&idt[0];
    idtr.limit = (uint16_t)sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS - 1;
 
    for (uint8_t vector = 0; vector < IDT_MAX_DESCRIPTORS - 1; vector++) 
    {
        idt_set_descriptor(vector, isr_stub_table[vector], 0x8E, 0);
        // vectors[vector] = true;
    }
    idt_set_descriptor(14, isr_stub_table[14], 0x8F, 2); // Not sure if this should be an exception (0x8F)
    __asm__ volatile ("lidt %0" : : "m"(idtr)); // load the new IDT
    __asm__ volatile ("sti"); // set the interrupt flag
}
