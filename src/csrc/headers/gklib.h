#ifndef GKLIB_H
#define GKLIB_H
#include <stddef.h>
#include <stdint-gcc.h>

extern void *memset(void *dst, int c, size_t n);
extern void *memcpy(void *dest, const void *src, size_t n);
extern size_t strlen(const char *s);
extern char *strcpy(char *dest, const char *src);
extern int strcmp(const char *s1, const char *s2);
extern const char *strchr(const char *s, int c);
uint8_t inb(uint16_t port);
void outb(uint16_t port, uint8_t val);

#endif // GKLIB_H
