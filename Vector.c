#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "Vector.h"

#ifdef __cplusplus
extern "C"{
#endif

MyVector_t* constructor(size_t data_size);
void move_constructor(MyVector_t*, void*);
void destructor(MyVector_t* self);
size_t getSize(MyVector_t* self);
size_t getCapacity(MyVector_t* self);
bool isEmpty(MyVector_t* self);
void* at(MyVector_t* self, int index);
void reserve(MyVector_t* self, size_t new_capacity);
void resize(MyVector_t* self, size_t new_size, void* fill_value);
void shrink_to_fit(MyVector_t* self);
void push_back(MyVector_t* self, void* data);
void pop_back(MyVector_t* self);
void insertAt(MyVector_t* self, void* data, int index);
void deleteAt(MyVector_t*, int index);

MyVector_t* constructor(size_t data_size){
  // Minimal Mem Reservation
  MyVector_t* obj = (MyVector_t*) my_malloc(sizeof(MyVector_t));
  // Member vatiables initialization
  obj->data = NULL;
  obj->data_size = data_size;
  obj->size = 0;
  obj->capacity = 0;
  // Assign function pointers with corresponding function address
  obj->p_move_constructor = move_constructor;
  obj->p_getCapacity = getCapacity;
  obj->p_getSize = getSize;
  obj->p_isEmpty = isEmpty;
  obj->p_at = at;
  obj->p_reserve = reserve;
  obj->p_resize = resize;
  obj->p_shrink_to_fit = shrink_to_fit;
  obj->p_push_back = push_back;
  obj->p_pop_back = pop_back;
  obj->p_insertAt = insertAt;
  obj->p_deleteAt = deleteAt;
  obj->p_destructor = destructor;
  return obj;
}

void move_constructor(MyVector_t* self, void* new_data){
  memcpy(new_data, self->data, self->data_size * self->size);
  my_free(self->data);
  self->data = new_data;
}

void destructor(MyVector_t* self){
  my_free(self->data);
  my_free(self);
}

size_t getSize(struct MyVector* self){
  printf("Vector size: %lu\n", self->size);
  return self->size;
}

size_t getCapacity(MyVector_t* self){
  return self->capacity;
}

bool isEmpty(MyVector_t* self){
  return self->size == 0;
}

void* at(MyVector_t* self, int index){
  if(self->size - 1 < index){
    printf("Accessing out of boundary...\n");
    printf("NULL will be returned...\n");
    return NULL;
  }

  void* target_ptr = (char*)self->data + index * self->data_size;
  for(int i = 0; i < self->data_size; i++){
    printf("At %p: %d\n", target_ptr + i, *(unsigned char*) (target_ptr+i));
  }
  return target_ptr;
}

void reserve(MyVector_t* self, size_t new_capacity){
  if(self->capacity >= new_capacity){
    printf("Vector has more capacity than needed!\n");
    return;
  }

  // Reserve mem block
  void* p_newMem = my_malloc(new_capacity * self->data_size);
  self->p_move_constructor(self, p_newMem);
  // NO COPY IMPLEMENTED YET
  printf("move/copy constructor not defined yet...\n");
  printf("size will be set to 0 for now...\n");
  self->capacity = new_capacity;
}

// C++14
// When new_size smaller then current size, call pop_back (size - new_size) times
// When larger, increase the capacity if needed, then fill up each elem to resize. 
#if CPP_VERSION >= 14
void resize(MyVector_t* self, size_t new_size, void* fill_value){
  if(new_size > self->size){
    if(self->capacity < new_size){
      // Reserve memory
      self->p_reserve(self, new_size);
      self->capacity = new_size;
    }
    int counter = new_size - self->size;
    while(counter != 0){
      self->p_push_back(self, fill_value);
      --counter;
    }
  }else{
    int counter = self->size - new_size;
    while(counter != 0){
      self->p_pop_back(self);
      --counter;
    }
  }
}
#endif

void shrink_to_fit(MyVector_t* self){
  void* p_newMem = my_malloc(self->size * self->data_size);
  self->p_move_constructor(self, p_newMem);
  return;
}

void push_back(MyVector_t* self, void* data){
  // Capacity & size check
  if(self->capacity == 0){
    printf("capacity is 0. 1 capacity will be reserved...\n");
    self->p_reserve(self, 1);
  } else if (self->size == self->capacity){
    // Resize
    printf("Capacity will be doubled\n");
    self->p_reserve(self, self->capacity*2);
  }

  // allocate memory
  void* des = self->data + self->data_size * self->size;
  void* src = data;
  printf("original data: %d\tcopied data: %d\n", *(int*)des, *(int*)src);
  memcpy(des, src, self->data_size);
  printf("des: %p src: %p\n", des, src);
  self->size += 1;
}

void pop_back(MyVector_t* self){
  if(self->p_isEmpty(self) == true){
    printf("Couldn't operate pop_back() because Vector is Empty...\n");
  }else{
    self->size--;
  }
}

void insertAt(MyVector_t* self, void* data, int index){
  if(self->size == self->capacity){
    self->p_reserve(self, self->capacity * 2);
  }

  void* src = self->data + self->data_size * index;
  void* des = src + self->data_size;
  // move right by 1 data
  memcpy(des, src, self->data_size * (self->size - index));
  memcpy(src, data, self->data_size);
  self->size += 1;
}

void deleteAt(MyVector_t* self, int index){
  // Validation
  
  // Move left by 1
  void* src = self->data + self->data_size * (index + 1);
  void* des = src - self->data_size;
  
  memcpy(des, src, self->data_size * (self->size - index - 1));
  self->size -= 1;
}

#ifdef __cpluplus
}
#endif
