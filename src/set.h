#ifndef xis_set_h_
#define xis_set_h_

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include "memory.h"
#include "val.h"

typedef enum {
  OP_RETURN,
  OP_NUMBER,
  OP_STRING,
  OP_CALL,
} opset_enum;

typedef struct {
  unsigned int capacity;
  unsigned int count;
  uint8_t* code;
  valarray constants;
  int* lines;
} opset;

void op_init(opset*);
void op_write(opset*,uint8_t,int);
void op_free(opset*);

unsigned int op_add_const(opset*,val);

#endif
