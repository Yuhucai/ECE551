#include <math.h>

#include <cstdio>
#include <cstdlib>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high);

class SinFunction : public Function<int, int>
{
 public:
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};

class nFunction : public Function<int, int>
{
 public:
  virtual int invoke(int arg) { return -1; }
};

class pFunction : public Function<int, int>
{
 public:
  virtual int invoke(int arg) { return 2; }
};

class linearFunction : public Function<int, int>
{
 public:
  virtual int invoke(int arg) { return arg; }
};

class CountedIntFn : public Function<int, int>
{
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n),
      f(fn),
      mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

void check(Function<int, int> * f, int low, int high, int expected_ans, const char * mesg) {
  int numbers;
  //maximum number of invocations of f
  if (high > low) {
    numbers = log(high - low) / log(2) + 1;
  }
  else {
    numbers = 1;
  }
  //warp f in a CountedIntFn
  CountedIntFn * function = new CountedIntFn(numbers, f, mesg);
  //perform the binary search
  int ans = binarySearchForZero(function, low, high);
  //check the answer
  if (ans != expected_ans) {
    fprintf(stderr, "Wrong output answer in %s\n", mesg);
    exit(EXIT_FAILURE);
  }
}

int main() {
  SinFunction f;
  nFunction nf;
  pFunction pf;
  linearFunction lf;
  check(&f, 0, 150000, 52359, "sinFunction");
  check(&nf, 1, 5, 4, "negative Function");
  check(&pf, 2, 10, 2, "positive Function");
  check(&lf, -99999, 10000000, 0, "linear Function");
  check(&lf, -99999999, -1000, -1001, "negative linear Function");
  check(&lf, 2, 100000000, 2, "positive linear Function");
  check(&lf, 0, 0, 0, "range");
  check(&lf, 10, 10, 10, "range");
  check(&lf, -1, 10000000, 0, "linear Function");
}
