#include "set.h"

#include <stdlib.h>

void op_init(opset* op) {
  op->count = 0;
  op->capacity = 0;
  op->code = NULL;
  op->lines = NULL;
  valarray_init(&op->constants);
}

void op_write(opset* op, uint8_t b, int line) {
  if(op->capacity < op->count + 1){
    int o = op->capacity;
    op->capacity = GROW_C(o);
    op->code = GROW(uint8_t, op->code, o, op->capacity);
    op->lines = GROW(int, op->lines, o, op->capacity);
  }
  op->lines[op->count] = line;
  op->code[op->count++] = b;
}

void op_free(opset* op) {
  GROW_FREE(uint8_t, op->code, op->capacity);
  GROW_FREE(int, op->lines, op->capacity);
  valarray_free(&op->constants);
  op_init(op);
}

unsigned int op_add_const(opset* op, val v){
  valarray_write(&op->constants, v);
  return op->constants.count - 1;
}
