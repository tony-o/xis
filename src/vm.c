#include "vm.h"
#include "debug.h"
#include "val.h"
#include "compiler.h"
#include "set.h"
#include <stdio.h>

void vm_init(VM* vm){
  vm_stack_reset(vm);
}

void vm_free(VM* vm){
  
}

vm_result vm_interpret(VM* vm, const char* src){
  opset o;
  op_init(&o);

  if(!compile(vm, src, &o)){
    op_free(&o);
    return VMR_COMPILE_ERR;
  }
  vm_result r = vm_run(vm);

  op_free(&o);
  return r;
}

vm_result vm_run(VM* vm){
  #define READ() (*vm->ip++)
  #define READC() (vm->op->constants.values[READ()])
  for(;;){
//    #ifdef DEBUG_TRACE_EXECUTION
    printf("          ");
    for (val* slot = vm->stack; slot < vm->stack_ptr; slot++) {
      printf("[ ");
      val_print(*slot);
      printf(" ]");
    }
    printf("\n");
    debug_op_disassemble_inst(vm->op, (int)(vm->ip - vm->op->code));
//    #endif
    uint8_t instr;
    switch(instr = READ()){
      case OP_RETURN:
        printf("ret: ");
        val_print(vm_stack_pop(vm));
        printf("\n");
        return VMR_OK;
      case OP_CONSTANT: {
        val v = READC();
        vm_stack_push(vm, v);
        break;
      }
      case OP_CALL: {
        val v = READC(); // # of args to for caller
        val x = 0;
        while (v > 0) {
          x += vm_stack_pop(vm);
          v--;
        }
        vm_stack_push(vm, x);
        break;
      }
    }
  }
  #undef READC
  #undef READ
}

void vm_stack_reset(VM* vm){
  vm->stack_ptr = vm->stack;
}

void vm_stack_push(VM* vm, val v){
  *(vm->stack_ptr++) = v;
}

val vm_stack_pop(VM* vm){
  return *(--vm->stack_ptr);
}
