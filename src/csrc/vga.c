#include "vga.h"
#include "gklib.h"

/** VGA Globals **/
static unsigned short *vgaBuff = (unsigned short *)VGA_BASE;
static int cursor = 0;
static int row = 0;
static int col = 0;

/** VGA Internal Functions **/
void cursor_newline()
{
   /* This will be replaced by VGA_scroll() */
   row += 1;
   col = 0;
   if (row == (HEIGHT + 1))
   {
      row = 0;
      col = 0;
   }
   cursor = row * WIDTH + col;
}

void cursor_mv()
{
   col += 1;
   if (col == (WIDTH + 1))
      cursor_newline();
   else
      cursor = row * WIDTH + col;
}

/** VGA Functions **/
void VGA_display_char(char c)
{
   vgaBuff[cursor] = VGA_CHAR(VGA_BRIGHT(VGA_GRAY), VGA_BLACK, c);
   cursor_mv();
}

void VGA_clear(void) 
{
   vgaBuff = memset(vgaBuff, '\0', WIDTH * HEIGHT);
}

void VGA_display_str(const char *str)
{
   int i = 0;
   for (; *(str + i) != '\0'; i++)
      VGA_display_char(*(str +i));
}
/**** END VGA ****/
