#ifndef GDT_H
#define GDT_H

#include <stdint-gcc.h>
#include "vga.h"
#define STACK_SIZE 256

typedef struct _GDTDescriptor
{
   uint16_t Size;
   uint64_t Offset;
} __attribute__((packed)) GDTDescriptor;

typedef struct _GDTEntry
{
   uint16_t limit0;
   uint16_t base0;
   uint8_t base1;
   uint8_t access;
   uint8_t limit1_flags;
   uint8_t base2;
} __attribute((packed)) GDTEntry;

typedef struct _TSSEntry
{
   uint16_t limit0;
   uint16_t base0;
   uint8_t base1;
   uint8_t access;
   uint8_t limit1_flags;
   uint8_t base2;
   uint32_t base3;
   uint32_t reserved;
} __attribute((packed)) TSSEntry;


typedef struct _GDT
{
   GDTEntry Null;
   GDTEntry KernelCode;
   GDTEntry KernelData;
   GDTEntry UserNull;
   GDTEntry UserCode;
   GDTEntry UserData;
   TSSEntry TSS;
   
} __attribute__((packed))
   __attribute((aligned(0x1000))) GDT;

typedef struct _TSS
{
   uint32_t reserved0;
   uint64_t rsp[3];
   uint64_t reserved1;
   uint64_t ist[7];
   uint64_t reserved2;
   uint16_t reserved3;
   uint16_t iomapbase;
} __attribute__ ((packed)) TSS;

extern GDT DefaultGDT;
extern void LoadGDT(GDTDescriptor *gdtdescriptor);
void gdt_init();

#endif // GDT_H
