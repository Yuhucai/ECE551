// This file is for Step 3.
// You should do
//  Step 3 (A): write seq3
//  Step 3 (B): write main to test seq3
//  Step 3 (C): write countEvenInSeq3Range
//  Step 3 (D): add test cases to main to test countEvenInSeq3Range
//
// Be sure to #include any header files you need!

#include <stdio.h>
#include <stdlib.h>

int seq3(int x, int y) {
  int ans;
  ans = (x + 2) * y - 3 * x;
  return ans;
}

int countEvenInSeq3Range(int xLow, int xHi, int yLow, int yHi) {
  if (xLow >= xHi || yLow >= yHi) {
    return 0;
  }
  else {
    int ans = 0;
    for (int x = xLow; x < xHi; x++) {
      for (int y = yLow; y < yHi; y++) {
        if (seq3(x, y) % 2 == 0) {
          ans++;
        }
      }
    }
    return ans;
  }
}

int main(void) {
  printf("seq3(%d, %d) = %d\n", -10, -10, seq3(-10, -10));
  printf("seq3(%d, %d) = %d\n", -5, -5, seq3(-5, -5));
  printf("seq3(%d, %d) = %d\n", -5, 4, seq3(-5, 4));
  printf("seq3(%d, %d) = %d\n", -1, 3, seq3(-1, 3));
  printf("seq3(%d, %d) = %d\n", 0, 0, seq3(0, 0));
  printf("seq3(%d, %d) = %d\n", 2, -3, seq3(2, -3));
  printf("seq3(%d, %d) = %d\n", 5, -5, seq3(5, -5));
  printf("seq3(%d, %d) = %d\n", 10, 20, seq3(10, 20));
  printf(
      "countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", 0, 2, 0, 3, countEvenInSeq3Range(0, 2, 0, 3));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         -5,
         5,
         -5,
         5,
         countEvenInSeq3Range(-5, 5, -5, 5));
  printf(
      "countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", 2, 0, 0, 3, countEvenInSeq3Range(2, 0, 0, 3));
  printf(
      "countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", 0, 2, 5, 1, countEvenInSeq3Range(0, 2, 5, 1));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         -10,
         10,
         -20,
         20,
         countEvenInSeq3Range(-10, 10, -20, 20));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         -20,
         20,
         -10,
         10,
         countEvenInSeq3Range(-20, 20, -10, 10));
  return 0;
}
