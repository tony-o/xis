#include "debug.h"

#include <stdio.h>

void debug_op_disassemble(opset* op, const char* n) {
  printf("===%s===\n", n);

  for(unsigned int offset=0; offset < op->count;){
    offset = debug_op_disassemble_inst(op, offset);
  }
}

int debug_op_disassemble_inst(opset* op, int offset){
  printf("%04d ", offset);
  uint8_t instr = op->code[offset];
  if(offset > 0 && op->lines[offset] == op->lines[offset-1]){
    printf("   | ");
  } else {
    printf("%4d ", op->lines[offset]);
  }
  switch(instr){
    case OP_RETURN:
      return debug_simple_instr("OP_RETURN", offset);
    case OP_NUMBER:
    case OP_STRING:
      return debug_const_instr("OP_CONSTANT", op, offset);
    case OP_CALL:
      return debug_const_instr("OP_CALL", op, offset);
    default:
      printf("Unknown opcode %d\n", instr);
      return offset + 1;
  }
}

int debug_simple_instr(const char* n, int o) {
  printf("%s\n", n);
  return o+1;
}

int debug_const_instr(const char* n, opset* o, int f){
  uint8_t c = o->code[f+1];
  printf("%-16s %4d '", n, c);
  val_print(o->constants.values[c]);
  printf("\n");
  return f + 2;
}
