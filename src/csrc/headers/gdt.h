#ifndef GDT_H
#define GDT_H

#include <stdint-gcc.h>
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

typedef struct _GDT
{
   GDTEntry Null;
   GDTEntry KernelCode;
   GDTEntry KernelData;
   GDTEntry UserNull;
   GDTEntry UserCode;
   GDTEntry UserData;
   
} __attribute__((packed))
   __attribute((aligned(0x1000))) GDT;

extern GDT DefaultGDT;
extern void LoadGDT(GDTDescriptor *gdtdescriptor);
void gdt_init();

#endif // GDT_H
