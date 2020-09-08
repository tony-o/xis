#include "scanner.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void scanner_init(scanner* sc, const char* src){
  sc->start = sc->current = src;
  sc->line = 1;
}

token scanner_token(scanner* sc){
  scanner_skipws(sc);

  sc->start = sc->current;
  if(scanner_eof(sc)){
    return scanner_make_token(sc, TOKEN_EOF);
  }

  printf("let's try again!\n");
  char c = scanner_advance(sc);
  switch(c){
    case ':': return scanner_make_token(sc, TOKEN_CALL);
    case '\0': return scanner_make_token(sc, TOKEN_EOF);
    case '"':
    case '\'':
      return scanner_consume_string(sc, c);
  }
  if(scanner_is_sym(sc)){
    return scanner_consume_sym(sc); //scanner_make_token(sc, TOKEN_SYMBOL);
  }
  return scanner_error(sc, "Unexpected character.");
}

int scanner_is_sym(scanner *sc){
  char c = *(sc->current);
  return ((c >= 'a' && c <= 'z')
     || (c >= 'A' && c <= 'Z')
     || (c >= '0' && c <= '9')
     || c == '-' || c == '?' || c == '<' || c == '=' || c == '_'
     || c == '>' || c == '+' || c == '!' || c == '*' || c == '\\'
     || c == '/')
    ? 1
    : 0;
}

token scanner_consume_string(scanner* sc, char e){
  while(*(++sc->current) != e && !scanner_eof(sc)){
    if(*(sc->current) == '\n'){
      sc->line++;
    }
    if(*(sc->current) == '\\' && *(sc->current+1) == e){
      scanner_advance(sc);
    }
  }
  scanner_advance(sc);
  return scanner_make_token(sc, TOKEN_LITERAL);
}

token scanner_consume_sym(scanner* sc){
  printf("START\n");
  while(scanner_is_sym(sc) && !scanner_eof(sc)){
    scanner_advance(sc);
    printf("ADVANCING\n");
  }
  printf("DON\n");
  char* a = malloc(sizeof(char) * ((int)(sc->current-sc->start) + 1));
  char* b;
  sprintf(a, "%.*s", (int)(sc->current - sc->start), sc->start);
  strtod(a, &b);
  if(a == b){
    free(a);
    printf("it's a symbol!\n");
    return scanner_make_token(sc, TOKEN_SYMBOL);
  }
  free(a);
  printf("it's a girl!\n");
  return scanner_make_token(sc, TOKEN_DOUBLE);

}

void scanner_skipws(scanner* sc){
  char c;
  for(;;){
    c = *(sc->current);
    switch(c){
      case '\n':
        sc->line++;
      case ' ':
      case '\r':
      case '\t':
        scanner_advance(sc);
        break;
      default: return;
    } 
  }
}

char scanner_advance(scanner* sc){
  sc->current++;
  return sc->current[-1];
}

int scanner_eof(scanner* sc){
  return *sc->current == '\0';
}

token scanner_make_token(scanner* sc, token_type tt){
  token t;
  t.type = tt;
  t.start = sc->start;
  t.line = sc->line;
  t.length = (int)(sc->current - sc->start);
  if (tt == TOKEN_DOUBLE){
    char* a = malloc(sizeof(char) * (t.length + 1));
    char* b;
    sprintf(a, "%.*s", t.length, sc->start);
    t.v = NUMVAL(strtod(a, &b));
    free(a);
  } else if (tt == TOKEN_LITERAL){
    char* a = malloc(sizeof(char) * (t.length + 1));
    sprintf(a, "%.*s", t.length, sc->start);
    t.v = STRVAL(a);
  }
  return t;
}

token scanner_error(scanner* sc, const char* err){
  token t;
  t.type = TOKEN_ERROR;
  t.start = err;
  t.length = (int)strlen(err);
  t.line = sc->line;
  return t;
}
