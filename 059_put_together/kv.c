#include "kv.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvarray_t * readKVs(const char * fname) {
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    perror("could not open file");
    return NULL;
  }
  kvarray_t * answer = malloc(sizeof(*answer));
  if (answer == NULL) {
    perror("malloc fails");
    return NULL;
  }
  answer->numparray = 0;
  answer->parray = NULL;
  char * buffer = NULL;  //store one line from file in buffuer
  size_t size = 0;
  size_t count = 0;
  while (getline(&buffer, &size, f) >= 0) {
    answer->numparray++;
    answer->parray = realloc(answer->parray, answer->numparray * sizeof(*answer->parray));
    if (answer->parray == NULL) {
      perror("malloc fails");
      return NULL;
    }
    kvpair_t * kv = malloc(sizeof(*kv));
    kv->key = buffer;
    //find key part
    char * p = strchr(kv->key, '=');
    if (p != NULL) {
      *p = '\0';
    }
    //find value part
    kv->value = p + 1;
    char * q = strchr(kv->value, '\n');
    if (q != NULL) {
      *q = '\0';
    }
    //store one pair in array
    answer->parray[count++] = kv;
    //new memory location for array
    buffer = NULL;
  }
  int result = fclose(f);
  assert(result == 0);
  free(buffer);
  return answer;
}

void freeKVs(kvarray_t * pairs) {
  for (int i = 0; i < pairs->numparray; i++) {
    free(pairs->parray[i]->key);
    free(pairs->parray[i]);
  }
  free(pairs->parray);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  for (int i = 0; i < (pairs->numparray); i++) {
    printf("key = '%s' value = '%s'\n", pairs->parray[i]->key, pairs->parray[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  char * v = NULL;
  for (int i = 0; i < pairs->numparray; i++) {
    if (strcmp(pairs->parray[i]->key, key) == 0) {
      v = pairs->parray[i]->value;
    }
  }
  return v;
}
