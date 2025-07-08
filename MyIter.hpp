#ifndef MY_ITER
#define MY_ITER

#include <stddef.h>

template<typename T>
class InputIter{
public:
  const T* p_data;

  InputIter(const T* ptr){
    this->p_data = ptr;
  }

  ~InputIter(){
    // data doesn't belong to this class
  }

  // Prefix ++ overloading
  InputIter& operator++(){
    this->p_data += 1;
    return *this;
  }

  // Postfix ++ overloading
  InputIter<T> operator++(int){
    InputIter<T> it = InputIter<T>(p_data);
    this->p_data++;
    return it;
  }

  const T operator*(){
    return *p_data;
  }
};

#endif
