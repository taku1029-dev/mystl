#ifndef VECTOR
#define VECTOR

#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>

#include "../my_memory_allocator/my_malloc.c"
#include "version.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef struct MyVector
{
  void* data;
  size_t data_size;
  size_t size;
  size_t capacity;
  
  struct MyVector* (*p_constructor)(size_t);
  void (*p_move_constructor)(struct MyVector*, void*); 
  void (*p_destructor)(struct MyVector*);

  // std::vector members
  size_t (*p_size)(struct MyVector*);
  size_t (*p_capacity)(struct MyVector*);
  bool (*p_isEmpty)(struct MyVector*);
  void* (*p_at)(struct MyVector*, int);
  void (*p_reserve)(struct MyVector*, size_t);
  void (*p_shrink_to_fit)(struct MyVector*);
  void (*p_resize)(struct MyVector*, size_t);
  void (*p_push_back)(struct MyVector*, void*);
  void (*p_pop_back)(struct MyVector*);
  void (*p_insertAt)(struct MyVector*, void*, int);
  void (*p_deleteAt)(struct MyVector*, int);

} MyVector_t;

#ifdef __cplusplus
}
#endif

#endif //VECTOR
