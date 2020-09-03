#ifndef xis_memory_h_
#define xis_memory_h_

#include <stdlib.h>

#define GROW_C(capacity) ((capacity) < 8 ? 8 : (capacity) * 2)
#define GROW(type, pointer, old, new) \
  (type*)reallocate(pointer, sizeof(type) * (old), \
                    sizeof(type) * (new))
#define GROW_FREE(type, pointer, o) \
  reallocate(pointer, sizeof(type) * (o), 0)

void* reallocate(void*, size_t, size_t);

#endif
