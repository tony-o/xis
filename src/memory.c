#include "memory.h"

#include <stdlib.h>
#include <stdio.h>

void* reallocate(void* ptr, size_t o, size_t n) {
  if(n == 0){
    free(ptr);
    return NULL;
  }
  void* result = realloc(ptr, n);
  if(result == 0){
    printf("Unable to allocate memory\n");
    exit(255);
  }
  return result;
}
