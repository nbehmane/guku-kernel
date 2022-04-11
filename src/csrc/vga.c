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
   vgaBuff[cursor] = VGA_DISP(VGA_BRIGHT(VGA_GRAY), VGA_BLACK, c);
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

/**** BEGIN PRINT FUNC ****/
extern void print_char(char c)
{
   VGA_display_char(c);
}

extern void print_str(const char *str)
{
   VGA_display_str(str);
}

extern void print_uchar(unsigned char c)
{
   unsigned char uc = c;
   vgaBuff[cursor] = VGA_DISP(VGA_BRIGHT(VGA_GRAY), VGA_BLACK, uc);
   cursor_mv();
}

extern void print_short(short shrt)
{
   short s = shrt;
   vgaBuff[cursor] = VGA_DISP(VGA_BRIGHT(VGA_GRAY), VGA_BLACK, s);
   cursor_mv();
}

extern char *convert16(long num)
{
   static char Rep[] = "0123456789ABCDEF";
   static char buffer[50];
   char *ptr;
   ptr = &buffer[49];
   *ptr = '\0';
   
   do
   {
      *--ptr = Rep[num % 16];
      num /= 16;
   } while (num != 0);

   return (ptr);
}

extern void print_long_hex(long num)
{
   char *con = convert16(num);
   VGA_display_str(con);
}
/**** END PRINT FUNC ****/









