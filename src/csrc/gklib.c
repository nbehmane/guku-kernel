#include "gklib.h"
/* TODO: strdup once malloc has been implemented. */

extern void *memset(void *dst, int c, size_t n)
{
   int i = 0;
   char *d = (char *)dst;

   for (; i < n; i++)
      *(d + i) = c;

   return dst;
}

extern void *memcpy(void *dest, const void *src, size_t n)
{
   int i = 0;
   char *d = (char *)dest;
   char *s = (char *)src;

   for (; i < n; i++)
      *(d + i) = *(s + i);

   return dest;
}

extern size_t strlen(const char *s)
{
   size_t len = 0;
   for (;;)
   {
      if (*s == '\0')
         break;
      s += 1;
      len += 1;
   }
   return len;
}

extern char *strcpy(char *dest, const char *src)
{
   int i = 0;
   size_t src_len = strlen(src);
   
   for (; i < src_len; i++)
      *(dest + i) = *(src + i);

   return dest;
}

extern int strcmp(const char *s1, const char *s2)
{
   int i = 0;
   char c1 = '\0';
   char c2 = '\0';
   int res = 0;

   for (;; i++)
   {
      c1 = *(s1 + i);
      c2 = *(s2 + i);

      if ((c1 - '\0') == 0 && (c2 - '\0') != 0)
      {
         res = c1 - c2;
         break;
      }
      if ((res = c1 - c2) == 0)
         if ((c1 - '\0') == 0)
            break;
      if ((res = c1 - c2) < 0)
         break;
      if ((res = c1 - c2) > 0)
         break;
   }
   return res;
}

extern const char *strchr(const char *s, int c)
{
   int i = 0; 

   for (;;)
      if (*(s + i) == c)
         break;
      else if (*(s + i) == '\0')
         break;

   return s + i;
}

uint8_t inb(uint16_t port)
{
   uint8_t ret;
   asm volatile ("inb %1, %0;" :"=a"(ret) :"Nd"(port));
   return ret;
}

void outb(uint16_t port, uint8_t val) 
{
   asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port));
}
