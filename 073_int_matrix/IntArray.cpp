#include "IntArray.h"

#include <assert.h>

#include <ostream>

//default constructor
IntArray::IntArray() : data(NULL), numElements(0) {}

//constructor with int
IntArray::IntArray(int n) : data(new int[n]), numElements(n) {}

//copy constructor
IntArray::IntArray(const IntArray & rhs) :
    data(new int[rhs.numElements]),
    numElements(rhs.numElements) {
  for (int i = 0; i < numElements; i++) {
    data[i] = rhs.data[i];
  }
}

//assignment operator
IntArray & IntArray::operator=(const IntArray & rhs) {
  if (this != &rhs) {
    int * temp = new int[rhs.numElements];
    for (int i = 0; i < rhs.numElements; i++) {
      temp[i] = rhs.data[i];
    }
    delete[] data;
    numElements = rhs.numElements;
    data = temp;
  }
  return *this;
}

//destructor
IntArray::~IntArray() {
  delete[] data;
}

// [] operator
const int & IntArray::operator[](int index) const {
  assert(index >= 0 && index < numElements);
  return data[index];
}

int & IntArray::operator[](int index) {
  assert(index >= 0 && index < numElements);
  return data[index];
}

//size function
int IntArray::size() const {
  return numElements;
}

// == operator
bool IntArray::operator==(const IntArray & rhs) const {
  if (numElements != rhs.numElements) {
    return false;
  }
  for (int i = 0; i < numElements; i++) {
    if (data[i] != rhs.data[i]) {
      return false;
    }
  }
  return true;
}

// != operator
bool IntArray::operator!=(const IntArray & rhs) const {
  return !((*this) == rhs);
}

// << operator
std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  if (rhs.size() == 0) {
    s << "{}";
    return s;
  }

  s << "{";
  for (int i = 0; i < rhs.size() - 1; i++) {
    s << rhs[i] << ", ";
  }
  s << rhs[rhs.size() - 1] << "}";
  return s;
}
