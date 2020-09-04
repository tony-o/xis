#include "compiler.h"
#include "scanner.h"
#include "set.h"

#include <stdio.h>
#include <stdlib.h>

char* tt_names[] = {
  "TOKEN_CALL", "TOKEN_EOF", "TOKEN_SYMBOL", "TOKEN_LITERAL", "TOKEN_DOUBLE", "TOKEN_ERROR"
};

int compile(VM* vm, const char* src, opset* o){
  scanner sc;
  scanner_init(&sc, src);

  parser p;
  p.had_error = p.panic = 0;
  p.op = *o;

  compiler_advance(&p, &sc);
  compiler_expression(vm, &p, &sc);
  compiler_consume(&p, &sc, TOKEN_EOF, "Expected end of expression.");
  compiler_end(vm, &p);
//  for(;;){
//    token t = scanner_token(&sc);
//    if(t.line != line){
//      printf("%4d ", t.line);
//      line = t.line;
//    } else {
//      printf("   | ");
//    }
//    printf("%-13s '%.*s'\n", tt_names[t.type], t.length, t.start);
//
//    if(t.type == TOKEN_EOF){
//      break;
//    }
//  }
  return !p.had_error;
}

void compiler_end(VM* vm, parser* p){
  compiler_emit(vm, p, OP_RETURN);
}

void compiler_expression(VM* vm, parser* p, scanner* sc){
  switch(p->current.type){
    case(OP_CONSTANT):
      compiler_emit(vm, p, OP_CONSTANT);
      break;
    default:
      compiler_error_at(p, "unexpected token.");
      break;
  }
}

void compiler_advance(parser* p, scanner* sc){
  p->previous = p->current;
  for(;;){
    p->current = scanner_token(sc);
    if(p->current.type != TOKEN_ERROR){
      break;
    }
    compiler_error_at(p, p->current.start);
  }
  token t = p->current;;
  if(t.line){
    printf("%4d ", t.line);
  }
  printf("%-13s '%.*s'\n", tt_names[t.type], t.length, t.start);
}

void compiler_emit(VM* vm, parser* p, uint8_t b){
  op_write(compiler_current_op(p), b, p->previous.line);
}

opset* compiler_current_op(parser* p){
  return &(p->op);
}

void compiler_consume(parser* p, scanner* sc, token_type t, const char* msg){
  if(p->current.type == t){
    compiler_advance(p, sc);
    return;
  }
  compiler_error_at(p, msg);
}

void compiler_error_at(parser* p, const char* msg){
  if(p->panic == 1){
    return;
  }
  p->panic = 1;

  token t = p->previous;
  fprintf(stderr, "[line %d] error: ", t.line);
  if(t.type == TOKEN_EOF){
    fprintf(stderr, "unexpected eof.");
  }else if(t.type == TOKEN_ERROR){}else{
    fprintf(stderr, "at '%.*s'", t.length, t.start);
  }
  fprintf(stderr, ": %s\n", msg);
  p->had_error = 1;
}