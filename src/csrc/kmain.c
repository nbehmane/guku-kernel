#include "vga.h"
#include "gklib.h"
#include "ps2.h"
#include "pic.h"
#include "irq.h"
#include "gdt.h"

/** Helpful Macros **/
#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

/** Globals **/
static uint8_t key = 0;

/**** BEGIN KMAIN ****/
int kmain()
{
   printk("Welcome to Guku OS!\n");

   printk("GDT initialization...\n");
   gdt_init();
   printk("ok.\n");

   printk("Keyboard initialization...");
   keyboard_init();
   printk("ok.\n");
   
   printk("PIC initialization...");
   PIC_init(0x20, 0x2F);
   printk("ok.\n");

   printk("IDT initialization...");
   idt_init();
   printk("ok.\n");

   printk("Clearing interrupt mask: 1 ...");
   IRQ_clear_mask(1);
   printk("ok.\n");

   register void *sp asm ("sp");
   printk("KMAIN SP %p\n", sp);
   printk("------------------\n");

   asm ("int $0x0e");

   while (TRUE)
   {
      key = key_get_resp();
   }
   

   for (;;)
      __asm__("hlt");
   return 0;
}
/**** END KMAIN ****/
