#include "vga.h"

/** VGA Globals **/
static unsigned short *vgaBuff = (unsigned short *)VGA_BASE;
static int width = 80;
static int height = 20;

/** VGA Functions **/
void VGA_display_char(int row, int col, char c)
{
   vgaBuff[row*width + col] = VGA_CHAR(VGA_BRIGHT(VGA_GRAY), VGA_BLACK, c);
}

void VGA_display_str(int row, int col, char *str, int len)
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
