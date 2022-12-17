#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tablec.h"

void tablec_init(struct hashtable *tablec, int max_capacity) {
  *tablec = (struct hashtable) {
    .max_capacity = max_capacity,
    .buckets = malloc(sizeof(struct hashtable_buckets) * max_capacity)
  };
}

size_t __tablec_mkIndex(struct hashtable *tablec, char *key) {
  size_t pos = 0;

  for (size_t i = 0; i < strlen(key); ++i){
    pos = pos * 37 + key[i];
  }

  return pos % tablec->max_capacity;
}

void tablec_set(struct hashtable *tablec, char *key, char *value) {
  size_t pos = __tablec_mkIndex(tablec, key);

  printf("%zu\n", pos);

  tablec->buckets[pos] = (struct hashtable_buckets) {
    .key = key,
    .value = value
  };
}

void tablec_del(struct hashtable *tablec, char *key) {
  size_t pos = __tablec_mkIndex(tablec, key);

  tablec->buckets[pos] = (struct hashtable_buckets) {
    .key = NULL,
    .value = NULL
  };
}

char *tablec_get(struct hashtable *tablec, char *key) {
  size_t pos = __tablec_mkIndex(tablec, key);

  return tablec->buckets[pos].value;
}

void tablec_cleanup(struct hashtable *tablec) {
  free(tablec->buckets);
}
