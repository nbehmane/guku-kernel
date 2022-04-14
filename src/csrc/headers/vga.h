#ifndef VGA_H
#define VGA_H

/** Includes **/
#include <stdarg.h>
#include "gklib.h"

/** VGA Macros **/
#define VGA_BASE 0xb8000
#define FG(color) ((color) & 0x0F)
#define BG(color) ((color) << 4)
#define VGA_DISP(fg, bg, ch) (((FG((fg)) | BG((bg))) << 8) | (ch))
#define VGA_BRIGHT(color) ((color) + 8)
#define WIDTH 80
#define HEIGHT 25

/** VGA Colors **/
#define VGA_BLACK      0
#define VGA_BLUE       1
#define VGA_GREEN      2
#define VGA_CYAN       3
#define VGA_RED        4
#define VGA_MAGENTA    5
#define VGA_BROWN      6
#define VGA_GRAY       7

void VGA_display_char(char c);
void VGA_clear(void);
void VGA_display_str(const char *str);
void VGA_cursor_newline();
void VGA_cursor_mv();
void VGA_scroll();
extern void print_char(char c);
extern void print_str(const char *str);
extern void print_uchar(unsigned char c);
extern void print_short(short shrt);
extern void print_long_hex(long num);
extern void print_int(int num);
extern void print_bin(int num);
extern int printk(char *fmt, ...);

#endif // VGA_H
