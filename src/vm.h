#ifndef xis_vm_h_
#define xis_vm_h_

#include "set.h"

#define VM_STACK_MAX 255

typedef struct {
  opset* op;
  uint8_t* ip;
  val stack[VM_STACK_MAX];
  val* stack_ptr;
} VM;

typedef enum {
  VMR_OK,
  VMR_COMPILE_ERR,
  VMR_RUNTIME_ERR,
} vm_result;

void vm_init(VM*);
void vm_free(VM*);

vm_result vm_interpret(VM*, const char*);

vm_result vm_run(VM*);
void vm_stack_reset(VM*);
void vm_stack_push(VM*,val);
val vm_stack_pop(VM*);

#endif
