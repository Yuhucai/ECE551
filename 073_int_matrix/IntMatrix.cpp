#include "IntMatrix.h"

#include "IntArray.h"

//default constructor
IntMatrix::IntMatrix() : numRows(0), numColumns(0), rows(NULL) {}

//constructor
IntMatrix::IntMatrix(int r, int c) : numRows(r), numColumns(c), rows(new IntArray *[r]) {
  for (int i = 0; i < r; i++) {
    rows[i] = new IntArray(c);
  }
}

//copy constructor
IntMatrix::IntMatrix(const IntMatrix & rhs) :
    numRows(rhs.numRows),
    numColumns(rhs.numColumns),
    rows(new IntArray *[numRows]) {
  for (int i = 0; i < numRows; i++) {
    rows[i] = new IntArray(rhs[i]);
  }
}

//destructor
IntMatrix::~IntMatrix() {
  for (int i = 0; i < numRows; i++) {
    delete rows[i];
  }
  delete[] rows;
}

//assignment operator
IntMatrix & IntMatrix::operator=(const IntMatrix & rhs) {
  if (this != &rhs) {
    //temp
    IntArray ** temprow = new IntArray *[rhs.numRows];
    for (int i = 0; i < rhs.numRows; i++) {
      temprow[i] = new IntArray(rhs[i]);
    }
    //delete
    for (int i = 0; i < numRows; i++) {
      delete rows[i];
    }
    delete[] rows;
    //assign
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    rows = temprow;
  }
  return *this;
}

//return row
int IntMatrix::getRows() const {
  return numRows;
}

//return column
int IntMatrix::getColumns() const {
  return numColumns;
}

//[] operator
const IntArray & IntMatrix::operator[](int index) const {
  assert(index >= 0 && index < numRows);
  return *rows[index];
}

IntArray & IntMatrix::operator[](int index) {
  assert(index >= 0 && index < numRows);
  return *rows[index];
}

//==operator
bool IntMatrix::operator==(const IntMatrix & rhs) const {
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
IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert(numRows == rhs.numRows && numColumns == rhs.numColumns);
  IntMatrix ans(numRows, numColumns);
  ans.numColumns = numColumns;
  ans.numRows = numRows;
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numColumns; j++) {
      ans[i][j] = (*this)[i][j] + rhs[i][j];
    }
  }
  return ans;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
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
