#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tablec.h"

void tablec_init(struct tablec_ht *tablec, struct tablec_bucket buckets[], size_t capacity) {
  tablec->length = 0;
  tablec->capacity = capacity;
  tablec->buckets = buckets;

  memset(tablec->buckets, 0, sizeof(struct tablec_bucket) * capacity);
}

static size_t _tablec_hash_idx(struct tablec_ht *tablec, char *key) {
  size_t hash = 0;
  
  while (*key != '\0') hash = hash * 37 + (*(key++) & 255);
  
  return hash % tablec->capacity;
}

int tablec_resize(struct tablec_ht *tablec, struct tablec_bucket new_buckets[], size_t new_capacity) {
  size_t old_capacity = tablec->capacity;
  size_t idx;

  if (new_capacity == old_capacity) {
    fputs("Expect new bucket!\n", stderr);
    abort();
  }

  tablec->capacity = new_capacity;

  memset(new_buckets, 0, sizeof(struct tablec_bucket) * new_capacity);

  while (old_capacity--) {

    if (tablec->buckets[old_capacity].key == NULL) continue;

    idx = _tablec_hash_idx(tablec, tablec->buckets[old_capacity].key);
    if (new_buckets[idx].key == NULL) {
      new_buckets[idx].key = tablec->buckets[old_capacity].key;
      new_buckets[idx].value = tablec->buckets[old_capacity].value;

      continue;
    }

    while ((new_buckets[idx].key != NULL) && (idx < tablec->capacity)) ++idx;

    if (idx == tablec->capacity) return -1;

    if (new_buckets[idx].key == NULL) {
      new_buckets[idx].key = tablec->buckets[old_capacity].key;
      new_buckets[idx].value = tablec->buckets[old_capacity].value;
    }
  }

  tablec->buckets = new_buckets;

  return 0;
}

int tablec_set(struct tablec_ht *tablec, char *key, void *value) {
  size_t idx;

  if ((tablec->length - 1) == tablec->capacity) return -1;

  idx = _tablec_hash_idx(tablec, key);
  while (idx != tablec->capacity) {
    if (tablec->buckets[idx].key == NULL) {
      tablec->buckets[idx].key = key;
      tablec->buckets[idx].value = value;

      ++tablec->length;

      return tablec->capacity - tablec->length + 1;
    }

    ++idx;
  }

  return -1;
}

void tablec_del(struct tablec_ht *tablec, char *key) {
  size_t idx = _tablec_hash_idx(tablec, key);
  while (idx != tablec->capacity) {
    if (tablec->buckets[idx].key != NULL && strcmp(tablec->buckets[idx].key, key) == 0) {
      tablec->buckets[idx].key = NULL;
      tablec->buckets[idx].value = NULL;
      tablec->length--;

      return;
    }

    ++idx;
  }
}

void *tablec_get(struct tablec_ht *tablec, char *key) {
  size_t idx = _tablec_hash_idx(tablec, key);
  while (idx != tablec->capacity) {
    if (tablec->buckets[idx].key != NULL && strcmp(tablec->buckets[idx].key, key) == 0)
      return tablec->buckets[idx].value;

    ++idx;
  }

  return NULL;
}
