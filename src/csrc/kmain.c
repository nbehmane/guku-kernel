/**** BEGIN VGA ****/
/** VGA Macros **/
#define VGA_BASE 0xb8000
#define FG(color) ((color) & 0x0F)
#define BG(color) ((color) << 4)
#define VGA_CHAR(fg, bg, ch) (((FG((fg)) | BG((bg))) << 8) | (ch))
#define VGA_BRIGHT(color) ((color) + 8)

/** VGA Colors **/
#define VGA_BLACK      0
#define VGA_BLUE       1
#define VGA_GREEN      2
#define VGA_CYAN       3
#define VGA_RED        4
#define VGA_MAGENTA    5
#define VGA_BROWN      6
#define VGA_GRAY       7

/** VGA Globals **/
static unsigned short *vgaBuff = (unsigned short *)VGA_BASE;
static int width = 80;
static int height = 20;

/** VGA Functions **/
extern void VGA_display_char(int row, int col, char c)
{
   vgaBuff[row*width + col] = VGA_CHAR(VGA_BRIGHT(VGA_GRAY), VGA_BLACK, c);
}

extern void VGA_display_str(int row, int col, char *str, int len)
{
   int i = 0;
   if (len == 0)
      while (*(str + i) != '\0')
      {
         VGA_display_char(row, col + i, *(str + i));
         i++;
      }
   else 
      for (; i < len; i++)
         VGA_display_char(row, col + i, *(str + i));
}
/**** END VGA ****/

/**** BEGIN KMAIN ****/
int kmain()
{
   VGA_display_str(0, 0, "Hello, world!", 0); 
   for (;;)
      __asm__("hlt");
   return 0;
}
