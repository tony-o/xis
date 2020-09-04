#ifndef xis_compiler_h_
#define xis_compiler_h_

#include "vm.h"
#include "set.h"
#include "scanner.h"

typedef struct {
  token current, previous;
  int had_error, panic;
  opset* op;
} parser;

int compile(VM*, const char*, opset*);
void compiler_advance(parser*, scanner*);
void compiler_consume(parser*, scanner*, token_type, const char*);
opset* compiler_current_op(parser*);
void compiler_error_at(parser*, const char*);
void compiler_emit(VM*, parser*, uint8_t);
void compiler_expression(VM*, parser*, scanner*);
void compiler_end(VM*, parser*);

#endif
