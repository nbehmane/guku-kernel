#define VGA_BASE 0xb8000
static unsigned short *vgaBuff = (unsigned short *)VGA_BASE;
static int width = 80;
static int height = 20;
static int cursor = 0;
static unsigned char color = (0 << 4) | (0xF & 0x0F);


void VGA_display_char(char c)
{
   vgaBuff[cursor] = ( color << 8) | c;
}

int kmain()
{
   VGA_display_char('A');
   for (;;)
      __asm__("hlt");
   return 0;
}
