#ifndef PS2_H
#define PS2_H
#include <stdint-gcc.h>

typedef struct _psCont
{
   uint8_t p1_irpt : 1;
   uint8_t p2_irpt : 1;
   uint8_t sf : 1;
   uint8_t zero : 1;
   uint8_t p1_clk : 1;
   uint8_t p2_clk : 1;
   uint8_t p1 : 1;
   uint8_t zero2 : 1;
} PSContConfig;

typedef struct _psStat
{
   uint8_t o_buff : 1;
   uint8_t i_buff : 1;
   uint8_t sf : 1;
   uint8_t cmd_data : 1;
   uint8_t unk1 : 1;
   uint8_t unk2 : 1;
   uint8_t t_out : 1;
   uint8_t p_error : 1;
} PSStatusReg;

typedef struct _psOutPort
{
   uint8_t sym_res : 1;
   uint8_t a20_out : 1;
   uint8_t p1_clk : 1;
   uint8_t p2_clk : 1;
   uint8_t p1_out_buf : 1;
   uint8_t p2_out_buf : 1;
   uint8_t p1_clk_out : 1;
   uint8_t p2_clk_out : 1;
} PSOutPort;





#endif
