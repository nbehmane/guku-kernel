/**** BEGIN VGA ****/
/* VGA Macros */
#define VGA_BASE 0xb8000
#define FG(color) ((color) & 0x0F)
#define BG(color) ((color) << 4)
#define VGA_CHAR(fg, bg, ch) (((FG((fg)) | BG((bg))) << 8) | (ch))
#define VGA_BRIGHT(color) ((color) + 8)

/* VGA Colors */
#define VGA_BLACK      0
#define VGA_BLUE       1
#define VGA_GREEN      2
#define VGA_CYAN       3
#define VGA_RED        4
#define VGA_MAGENTA    5
#define VGA_BROWN      6
#define VGA_GRAY 7

/* VGA Globals */
static unsigned short *vgaBuff = (unsigned short *)VGA_BASE;
static int width = 80;
static int height = 20;
static int cursor = 0;

/* VGA Functions */
extern void VGA_display_char(char c)
{
   vgaBuff[cursor++] = VGA_CHAR(VGA_BRIGHT(VGA_GRAY), VGA_BLACK, c);
}
/**** END VGA ****/

/**** BEGIN KMAIN ****/
int kmain()
{
   VGA_display_char('H');
   VGA_display_char('E');
   VGA_display_char('L');
   VGA_display_char('L');
   VGA_display_char('O');
   VGA_display_char('!');
   for (;;)
      __asm__("hlt");
   return 0;
}
