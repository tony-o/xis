#ifndef xis_val_h_
#define xis_val_h_

typedef double val;

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
