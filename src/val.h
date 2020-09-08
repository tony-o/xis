#ifndef xis_val_h_
#define xis_val_h_

typedef enum {
  VAL_STRING,
  VAL_NUMBER,
} valtype;

typedef struct {
  valtype type;
  union {
    char* string;
    double number;
  } as;
} val;

#define STRVAL(v) ((val){VAL_STRING, {.string = v} })
#define NUMVAL(v) ((val){VAL_NUMBER, {.number = v} })
#define AS_STR(v) ((v).as.string)
#define AS_NUM(v) ((v).as.number)

typedef struct {
  int capacity;
  int count;
  val* values;
} valarray;

void valarray_init(valarray*);
void valarray_write(valarray*,val);
void valarray_free(valarray*);

void val_print(val);

#endif
