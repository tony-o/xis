#ifndef xis_debug_h_
#define xis_debug_h_

#include "set.h"

void debug_op_disassemble(opset*, const char*);
int debug_op_disassemble_inst(opset*, int offset);
int debug_simple_instr(const char*, int);
int debug_const_instr(const char*, opset* , int);

#endif
