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
  for(int i=0; i<v->count;i++){
    if(v->values[i].type == VAL_STRING){
      free(AS_STR(v->values[i]));
    }
  }
  GROW_FREE(val, v->values, v->capacity);
  valarray_init(v);
}

void val_print(val v){
  if(v.type == VAL_STRING){
    printf("%s", (const char*)AS_STR(v));
  }else if(v.type == VAL_NUMBER){
    printf("%g", (double)AS_NUM(v));
  }
}
