#include "boundvalue.h"
#include "kernel.h"

#include <cstring>
#include <iostream>
#include <type_traits>


/*******************************************************/
//  Constant scalars
/*******************************************************/
// template<typename T>
// BoundScalar::BoundScalar(T val) {
//   if( std::is_trivial<T>::value == false) {
//     raiseError("The scalar type is not trivially copyable");
//   }

//   size = sizeof(T);
//   scalar = new char[size];

//   T * scalarT = (T*)scalar;
//   *scalarT = val;
// }

BoundScalar::BoundScalar(BoundScalar&& bs) {
  size = bs.size;
  scalar = new char[size];
  for(int i = 0; i < size; i++) { scalar[i] = bs.scalar[i]; }
}

BoundScalar::~BoundScalar() {
  delete scalar;
}

// template<typename T>
// T BoundScalar::getValue

/*******************************************************/
//  Buffers
/*******************************************************/
BoundBuffer::BoundBuffer(cl_mem b, uint s) {
  size = s;
  buffer = b;
}

BoundBuffer::BoundBuffer(BoundBuffer&& bb) {
  size = bb.size;
  buffer = bb.buffer;
}

BoundBuffer::~BoundBuffer() {}

BoundBuffer::operator cl_mem() {
  return buffer;
}

uint BoundBuffer::getSize() {
  return size;
}

/*******************************************************/
//  Promises
/*******************************************************/
template<typename T>
BoundPromise<T>::BoundPromise(Kernel<T> * k, uint s, uint t) {
  sourceKernel = k;
  sourceArgPos = s;
  targetArgPos = t;
}

template<typename T>
BoundPromise<T>::BoundPromise(BoundPromise&& bp) {
  sourceKernel = bp.sourceKernel;
  sourceArgPos = bp.sourceArgPos;
  targetArgPos = bp.targetArgPos;
}

template<typename T>
BoundPromise<T>::~BoundPromise() {}

template<typename T>
uint BoundPromise<T>::getSize() {
  return size;
}

template class BoundPromise<int>;
template class BoundPromise<float>;
template class BoundPromise<double>;
