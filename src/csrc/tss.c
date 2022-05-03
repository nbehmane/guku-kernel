#include "tss.h"

#ifndef DEBUG
#define DEBUG 1
#endif

static uint32_t tss[32];

typedef struct _tss 
{
   uint16_t seg_limit;
   uint16_t base_low;
   uint8_t  base_mid;
   uint8_t  attr;
   uint8_t  seg_limit_high : 4;
   uint8_t AVL : 1;
   uint8_t :2;
   uint8_t G: 1;
   uint8_t base_high;
   uint32_t base_high_2; 
   uint64_t res;
   
} __attribute__((packed)) tss_entry_t;

tss_entry_t tss_descriptor;

void init_tss(uint64_t *gdt)
{
   tss_descriptor.seg_limit = 0;
   tss_descriptor.base_low = ((uint64_t)tss) & 0x0000FFFF;
   tss_descriptor.base_mid = ((((uint64_t)tss) & 0x00FF0000) >> 16);
   tss_descriptor.attr = 0x89;
   tss_descriptor.G = 1;
   tss_descriptor.base_high = ((((uint64_t)tss) & 0xFF000000) >> 24);
   tss_descriptor.base_high_2 =  ((((uint64_t)tss) & 0xFFFFFFFF00000000) >> 32);

   #if DEBUG
   printk("TSS ADDRESS: %x\n", (unsigned long)tss);
   printk("TSS BASE_LOW: %x\n", (unsigned long)tss_descriptor.base_low);
   printk("TSS BASE_MID: %x\n", (unsigned long)tss_descriptor.base_mid);
   printk("TSS BASE_HIGH: %x\n", (unsigned long)tss_descriptor.base_high);
   printk("TSS BASE_HIGH_2: %x\n", (unsigned long)tss_descriptor.base_high_2);
   #endif
   // Copy the tss_descriptor to the gdt
   memcpy(gdt + 2, &tss_descriptor, sizeof(tss_descriptor));

   (void)tss_descriptor;
}
