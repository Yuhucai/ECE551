#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>
#include <fstream>
#include <string>

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}

uint64_t * readFrequencies(const char * fname) {
  std::ifstream reader;
  //read file
  reader.open(fname);
  if (reader.fail()) {
    std::cerr << "cannot read from file" << std::endl;
    exit(EXIT_FAILURE);
  }
  uint64_t * ans = new uint64_t[257]();
  int c = 0;
  while ((c = reader.get()) != EOF) {
    ans[c]++;
  }
  //EOF
  ans[256]++;
  reader.close();
  return ans;
}
