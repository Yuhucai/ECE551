#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void count(FILE * f, int * array) {
  int c;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      array[c - 97]++;
    }
  }
}

int numberfore(int * array, int n) {
  int index = 0;
  for (int i = 1; i < n; i++) {
    if (array[i] > array[index]) {
      index = i;
    }
  }
  return index + 97;
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: breaker inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  int array[26] = {0};
  count(f, array);
  int e = numberfore(array, 26);
  int key;
  if (e >= 101) {
    key = e - 101;
  }
  else {
    key = 26 + e - 101;
  }
  fprintf(stdout, "%d\n", key);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
