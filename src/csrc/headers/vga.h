#ifndef VGA_H
#define VGA_H

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

void VGA_display_char(int row, int col, char c);
void VGA_display_str(int row, int col, char *str, int len);


#endif // VGA_H
