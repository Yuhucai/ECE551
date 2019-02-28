// This file is for Step 2.
// You should do
//  Step 2 (A): write seq2
//  Step 2 (B): write main to test seq2
//  Step 2 (C): write sumSeq2
//  Step 2 (D): add test cases to main to test sumSeq2
//
// Be sure to #include any header files you need!

#include <stdio.h>
#include <stdlib.h>

int seq2(int x) {
  int ans;
  ans = (x + 1) * (x + 1) + x;
  return ans;
}

int sumSeq2(int low, int high) {
  if (low >= high) {
    return 0;
  }
  else {
    int ans = 0;
    for (int x = low; x < high; x++) {
      ans = ans + seq2(x);
    }
    return ans;
  }
}

int main(void) {
  printf("seq2(%d) = %d\n", -10, seq2(-10));
  printf("seq2(%d) = %d\n", -4, seq2(-4));
  printf("seq2(%d) = %d\n", -3, seq2(-3));
  printf("seq2(%d) = %d\n", -2, seq2(-2));
  printf("seq2(%d) = %d\n", -1, seq2(-1));
  printf("seq2(%d) = %d\n", 0, seq2(0));
  printf("seq2(%d) = %d\n", 1, seq2(1));
  printf("seq2(%d) = %d\n", 10, seq2(10));
  printf("sumSeq2(%d, %d) = %d\n", 0, 2, sumSeq2(0, 2));
  printf("sumSeq2(%d, %d) = %d\n", 3, 6, sumSeq2(3, 6));
  printf("sumSeq2(%d, %d) = %d\n", 9, 7, sumSeq2(9, 7));
  printf("sumSeq2(%d, %d) = %d\n", 5, 5, sumSeq2(5, 5));
  printf("sumSeq2(%d, %d) = %d\n", -5, 10, sumSeq2(-5, 10));
  return 0;
}
