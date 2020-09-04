#ifndef xis_scanner_h_
#define xis_scanner_h_

typedef struct {
  const char* start;
  const char* current;
  int line;
} scanner;

typedef enum {
  TOKEN_CALL, TOKEN_EOF, TOKEN_SYMBOL, TOKEN_LITERAL, TOKEN_DOUBLE, TOKEN_ERROR,
} token_type;

typedef struct {
  token_type type;
  const char* start;
  int length;
  int line;
} token;

void scanner_init(scanner*, const char*);
token scanner_token(scanner*);
char scanner_advance(scanner*);
void scanner_skipws(scanner*);

int scanner_eof(scanner*);
int scanner_is_sym(scanner*);
token scanner_make_token(scanner*, token_type);
token scanner_error(scanner*, const char*);

token scanner_consume_sym(scanner*);
token scanner_consume_string(scanner*, char);

#endif
