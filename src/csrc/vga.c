#include "vga.h"
#include "gklib.h"

/** VGA Globals **/
static unsigned short *vgaBuff = (unsigned short *)VGA_BASE;
static int cursor = 0;
static int row = 0;
static int col = 0;

/** VGA Internal Functions **/
void VGA_cursor_newline()
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
      VGA_cursor_newline();
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
   VGA_cursor_newline();
}
/**** END VGA ****/

/**** BEGIN PRINT FUNC ****/
extern char *convert(long num, int base, int neg)
{
   static char Rep[] = "0123456789ABCDEF";
   static char buffer[50];
   char *ptr;
   int flag = 0;
   ptr = &buffer[49];
   *ptr = '\0';

   if (num < 0 && neg == 1)
   {
      flag = 1;
      num *= -1;
   }

   do
   {
      *--ptr = Rep[num % base];
      num /= base;
   } while (num != 0);

   if (flag)
      *--ptr = '-';

   return (ptr);
}

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
   char *res = convert(uc, 10, 0);
   VGA_display_str(res);
}

extern void print_short(short shrt)
{
   short s = shrt;
   char *res = convert(s, 10, 0);
   VGA_display_str(res);
}

extern void print_long_hex(long num)
{
   char *res = convert(num, 16, 0);
   VGA_display_str(res);
}

extern void print_int(int num)
{
   char *res = convert(num, 10, 1);
   VGA_display_str(res);
}

extern void print_bin(int num)
{
   char *res = convert(num, 2, 0);
   VGA_display_str(res);
}
















/**** END PRINT FUNC ****/
