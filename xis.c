#include <stdio.h>
#include "xis.h"

int main(int argc, const char* argv[]) {
  VM vm;
  vm_init(&vm);
  opset o;
  op_init(&o);
  for(val i=1;i<4;i++){
    op_write(&o, OP_CONSTANT, 1);
    op_write(&o, op_add_const(&o, i), 1);
  }
  op_write(&o, OP_CALL, 2);
  op_write(&o, op_add_const(&o, 3), 2);

  op_write(&o, OP_RETURN, 2);

  debug_op_disassemble(&o, "test");
  printf("==output==\n\n");
  vm_interpret(&vm, &o);
  vm_free(&vm);
  op_free(&o);
  return 0;
}
