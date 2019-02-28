#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);  //prototype for power

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  unsigned ans = power(x, y);
  if (ans == expected_ans) {
    printf("The power function passes the test case\n");
  }
  else {
    printf("The power function fails the test case\n");
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  run_check(2, 0, 1);
  run_check(0, 0, 1);
  run_check(-2, 3, -8);
  run_check(2, 3, 8);
  run_check(0, 0, 1);
  return (EXIT_SUCCESS);
}
