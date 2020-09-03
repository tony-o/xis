#include <stdio.h>
#include "xis.h"

int main(int argc, const char* argv[]) {
  VM vm;
  vm_init(&vm);
  opset o;
  op_init(&o);
  int x = op_add_const(&o, 1.2);
  op_write(&o, OP_CONSTANT, 1);
  op_write(&o, x, 1);

  op_write(&o, OP_RETURN, 2);
  op_write(&o, OP_RETURN, 2);

//  debug_op_disassemble(&o, "test");
  vm_interpret(&vm, &o);
  vm_free(&vm);
  op_free(&o);
  return 0;
}
