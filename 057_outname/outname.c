#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  const char * suffix = ".counts";
  unsigned len = strlen(inputName) + strlen(suffix) + 1;
  char * ans = malloc(len * sizeof(*ans));
  snprintf(ans, len, "%s%s", inputName, suffix);
  return ans;
}
