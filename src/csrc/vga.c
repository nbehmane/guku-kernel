#include "vga.h"

/** VGA Globals **/
static unsigned short *vgaBuff = (unsigned short *)VGA_BASE;
static int cursor = 0;
static int row = 0;
static int col = 0;

/** VGA Internal Functions **/
void VGA_scroll()
{
   int i = 0;
   memset(vgaBuff, '\0', WIDTH);
   for (; i < HEIGHT; i++)
      memcpy(&vgaBuff[i * WIDTH], &vgaBuff[(i + 1) * WIDTH], WIDTH);
}

void VGA_cursor_newline()
{
   /* This will be replaced by VGA_scroll() */
   row += 1;
   col = 0;
   if (row == (HEIGHT + 1))
   {
      row = HEIGHT;
      col = 0;
      VGA_scroll();
   }
   cursor = row * WIDTH + col;
}

void cursor_mv()
{
   col += 1;
   if (col == WIDTH)
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
      VGA_display_char(*(str + i));
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

extern void print_long(long num)
{
   char *res = convert(num, 10, 0);
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

extern int printk(char *fmt, ...)
{
   char *traverse;
   size_t i;
   char *s;
   va_list arg;

   va_start(arg, fmt);
   for (traverse = fmt; *traverse != '\0'; traverse++)
   {
      while (*traverse != '%') 
      {
         if (*traverse == '\n')
         {
            VGA_cursor_newline();
            traverse++;
            continue;
         }
         if (*traverse == '\0')
            return 0;
         VGA_display_char(*traverse);
         traverse++;
      }

      traverse++;
      switch (*traverse)
      {
         case 'd': i = va_arg(arg, int);
            print_int(i);
            break;
         case 'c': i = va_arg(arg, int);
            print_char(i);
            break;
         case 'u': i = va_arg(arg, int);
            print_uchar(i);
            break;
         case 'x': i = va_arg(arg, long);
            print_long_hex(i);
            break;
         case 'b': i = va_arg(arg, int);
            print_bin(i);
            break;
         case 's': s = va_arg(arg, char *); 
            print_str(s);
            break;
         case '%': print_char('%');
            break;
         case 'l': i = va_arg(arg, long);
            print_long(i);
            break;
         default: print_str("printk: not valid.\n");
            break;
      }
   }
   va_end(arg);

   return 0;
}
/**** END PRINT FUNC ****/
