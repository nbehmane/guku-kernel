#include "ps2.h"

void set_stat(PSStatusReg *reg)
{
   reg->o_buff = 0;
   reg->i_buff = 0;
   reg->cmd_data = 1;
}
