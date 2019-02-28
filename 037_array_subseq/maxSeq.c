#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  size_t answer = 0;
  size_t temp = 1;
  if (n > 0) {
    for (size_t i = 1; i < n; i++) {
      if (array[i] > array[i - 1]) {
        temp++;
      }
      else {
        if (answer < temp) {
          answer = temp;
        }
        temp = 1;
      }
    }
    if (answer < temp) {
      answer = temp;
    }
  }
  return answer;
}
