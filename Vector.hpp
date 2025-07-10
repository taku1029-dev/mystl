#ifndef VECTER_WRAPPER
#define VECTER_WRAPPER

#include "Vector.h"

template  <typename T>
class MyVectorWrapper{
public:
  MyVector_t* cVector;
  size_t data_size;

  MyVectorWrapper(){
    this->cVector = constructor();
    this->data_size = sizeof(T);
  }
  // Copy constructor
  MyVectorWrapper(MyVectorWrapper* other);
  ~MyVectorWrapper(){
    destructor(cVector);
  }

  // Operator Overloading
  T& operator[](int index);
  
  MyVectorWrapper operator=(MyVectorWrapper* other){
    return MyVectorWrapper(other);
  }
  MyVectorWrapper operator==(MyVectorWrapper* other);
  MyVectorWrapper operator!=(MyVectorWrapper* other);

  void resize_wrapper();
  void reserve_wrapper();

};

#endif
