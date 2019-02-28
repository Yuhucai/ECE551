#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

template<typename T>
class Matrix
{
 private:
  int numRows;
  int numColumns;
  std::vector<T> ** rows;

 public:
  //default constructor
  Matrix() : numRows(0), numColumns(0), rows(NULL) {}

  //constructor
  Matrix(int r, int c) : numRows(r), numColumns(c), rows(new std::vector<T> *[r]) {
    for (int i = 0; i < r; i++) {
      rows[i] = new std::vector<T>(c);
    }
  }

  //copy constructor
  Matrix(const Matrix & rhs) :
      numRows(rhs.numRows),
      numColumns(rhs.numColumns),
      rows(new std::vector<T> *[numRows]) {
    for (int i = 0; i < numRows; i++) {
      rows[i] = new std::vector<T>(rhs[i]);
    }
  }

  //destructor
  ~Matrix() {
    for (int i = 0; i < numRows; i++) {
      delete rows[i];
    }
    delete[] rows;
  }

  //assignment operator
  Matrix & operator=(const Matrix & rhs) {
    if (this != &rhs) {
      //temp
      std::vector<T> ** temp = new std::vector<T> *[rhs.numRows];
      for (int i = 0; i < rhs.numRows; i++) {
        temp[i] = new std::vector<T>(rhs[i]);
      }
      //delete
      for (int i = 0; i < numRows; i++) {
        delete rows[i];
      }
      delete[] rows;
      //assgign
      numRows = rhs.numRows;
      numColumns = rhs.numColumns;
      rows = temp;
    }
    return *this;
  }

  //return row
  int getRows() const { return numRows; }

  //return column
  int getColumns() const { return numColumns; }

  //[]operator
  const std::vector<T> & operator[](int index) const {
    assert(index >= 0 && index < numRows);
    return *rows[index];
  }

  std::vector<T> & operator[](int index) {
    assert(index >= 0 && index < numRows);
    return *rows[index];
  }

  //==operator
  bool operator==(const Matrix & rhs) const {
    if (numRows != rhs.numRows || numColumns != rhs.numColumns) {
      return false;
    }
    for (int i = 0; i < numRows; i++) {
      if ((*this)[i] != rhs[i]) {
        return false;
      }
    }
    return true;
  }

  //+operator
  Matrix operator+(const Matrix & rhs) const {
    assert(numRows == rhs.numRows && numColumns == rhs.numColumns);
    Matrix ans(numRows, numColumns);
    ans.numRows = numRows;
    ans.numColumns = rhs.numColumns;
    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numColumns; j++) {
        ans[i][j] = (*this)[i][j] + rhs[i][j];
      }
    }
    return ans;
  }
};

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  if (rhs.getRows() == 0) {
    s << "[  ]";
    return s;
  }
  s << "[ ";
  for (int i = 0; i < rhs.getRows() - 1; i++) {
    s << rhs[i] << ",\n";
  }
  s << rhs[rhs.getRows() - 1] << " ]";
  return s;
}

template<typename T>
std::ostream & operator<<(std::ostream & s, const std::vector<T> & rhs) {
  if (rhs.size() == 0) {
    s << "{  }";
    return s;
  }
  s << "{ ";
  for (size_t i = 0; i < rhs.size() - 1; i++) {
    s << rhs[i] << ",";
  }
  s << rhs[rhs.size() - 1] << " }";
  return s;
}

#endif
