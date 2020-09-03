#include "val.h"
#include "memory.h"

#include <stdio.h>

void valarray_init(valarray* v){
  v->values = NULL;
  v->capacity = 0;
  v->count = 0;
}

void valarray_write(valarray* v, val w){
  if(v->capacity < v->count + 1){
    int o = v->capacity;
    v->capacity = GROW_C(o);
    v->values = GROW(val, v->values, o, v->capacity);
  }
  v->values[v->count++] = w;
}

void valarray_free(valarray* v){
  GROW_FREE(val, v->values, v->capacity);
  valarray_init(v);
}

void val_print(val v){
  printf("%g", v);
}
