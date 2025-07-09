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

template<typename T>
class OutputIter{
private:
  T* p_data;

  class Proxy{
  private:
    T* ptr;
  public:
    Proxy(T* ptr){
      this->ptr = ptr;
    }
    void operator=(const T& data){
      *ptr = data;
    }
  };
public:
  OutputIter(T* ptr){
    this->p_data = ptr;
  }

  OutputIter& operator++(){
    this->p_data += 1;
    return *this;
  }

  OutputIter<T> operator++(int){
    OutputIter<T> it = OutputIter<T>(p_data);
    this->p_data++;
    return it;
  }

  Proxy operator*(){
    return Proxy(p_data);
  }
};

template<typename T>
class ForwardIter{
public:
  T* p_data;

  ForwardIter(T* ptr){
    this->p_data = ptr;
  }

  // Prefix ++ overloading
  ForwardIter& operator++(){
    this->p_data += 1;
    return *this;
  }

  // Postfix ++ overloading
  ForwardIter<T> operator++(int){
    ForwardIter<T> it = ForwardIter<T>(p_data);
    this->p_data++;
    return it;
  }

  T& operator*(){
    return *p_data;
  }
};

template<typename T>
class BidirectionalIter{
public:
  T* p_data;

  BidirectionalIter(T* ptr){
    this->p_data = ptr;
  }

  // Prefix overloading
  BidirectionalIter& operator++(){
    this->p_data += 1;
    return *this;
  }

  BidirectionalIter<T> operator--(){
    this->p_data -= 1;
    return *this;
  }

  // Postfix overloading
  BidirectionalIter<T> operator++(int){
    BidirectionalIter<T> it = BidirectionalIter<T>(p_data);
    this->p_data++;
    return it;
  }

  BidirectionalIter<T> operator--(int){
    BidirectionalIter<T> it = BidirectionalIter<T>(p_data);
    this->p_data--;
    return it;
  }

  T& operator*(){
    return *p_data;
  }
};

#endif
