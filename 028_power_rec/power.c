#include <stdio.h>
#include <stdlib.h>

unsigned power_helper(unsigned x, unsigned y, unsigned ans) {
  if (y <= 0) {
    return ans;
  }
  if (x == 0) {
    return 0;
  }
  return power_helper(x, y - 1, ans * x);
}

unsigned power(unsigned x, unsigned y) {
  return power_helper(x, y, 1);
}
