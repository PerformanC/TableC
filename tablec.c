#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tablec.h"

void tablec_oanm_init(struct tablec_oanm_ht *tablec, struct tablec_oanm_bucket buckets[], size_t capacity) {
  tablec->length = 0;
  tablec->capacity = capacity;
  tablec->buckets = buckets;

  memset(tablec->buckets, 0, sizeof(struct tablec_oanm_bucket) * capacity);
}

static size_t _tablec_oanm_hash(struct tablec_oanm_ht *tablec, char *key) {
  size_t hash = 0;
  
  while (*key != '\0') hash = hash * 37 + (*(key++) & 255);
  
  return hash % tablec->capacity;
}

int tablec_oanm_resize(struct tablec_oanm_ht *tablec, struct tablec_oanm_bucket new_buckets[], size_t new_capacity) {
  size_t old_capacity = tablec->capacity;
  size_t hash;

  tablec->capacity = new_capacity;

  memset(new_buckets, 0, sizeof(struct tablec_oanm_bucket) * new_capacity);

  while (old_capacity--) {
    if (tablec->buckets[old_capacity].key == NULL) continue;

    hash = _tablec_oanm_hash(tablec, tablec->buckets[old_capacity].key);

    if (new_buckets[hash].key == NULL) {
      new_buckets[hash].key = tablec->buckets[old_capacity].key;
      new_buckets[hash].value = tablec->buckets[old_capacity].value;

      continue;
    }

    while ((new_buckets[hash].key != NULL) && (hash < tablec->capacity)) hash++;

    if (hash == tablec->capacity) return -1;

    if (new_buckets[hash].key == NULL) {
      new_buckets[hash].key = tablec->buckets[old_capacity].key;
      new_buckets[hash].value = tablec->buckets[old_capacity].value;
    }
  }

  tablec->buckets = new_buckets;

  return 0;
}

int tablec_oanm_set(struct tablec_oanm_ht *tablec, char *key, void *value) {
  size_t hash;

  if ((tablec->length - 1) == tablec->capacity) return -1;

  hash = _tablec_oanm_hash(tablec, key);

  while (hash != tablec->capacity) {
    if (tablec->buckets[hash].key == NULL) {
      tablec->buckets[hash].key = key;
      tablec->buckets[hash].value = value;

      tablec->length++;

      return tablec->capacity - tablec->length + 1;
    }

    hash++;
  }

  return -1;
}

void tablec_oanm_del(struct tablec_oanm_ht *tablec, char *key) {
  size_t hash = _tablec_oanm_hash(tablec, key);

  while (hash != tablec->capacity) {
    if (tablec->buckets[hash].key != NULL && strcmp(tablec->buckets[hash].key, key) == 0) {
      tablec->buckets[hash].key = NULL;
      tablec->buckets[hash].value = NULL;

      tablec->length--;

      return;
    }

    hash++;
  }
}

struct tablec_oanm_bucket *tablec_oanm_get(struct tablec_oanm_ht *tablec, char *key) {
  size_t hash = _tablec_oanm_hash(tablec, key);

  while (hash != tablec->capacity) {
    if (tablec->buckets[hash].key != NULL && strcmp(tablec->buckets[hash].key, key) == 0)
      return &tablec->buckets[hash];

    hash++;
  }

  return NULL;
}

size_t tablec_oanm_full(struct tablec_oanm_ht *tablec) {
  return (int)(tablec->capacity == tablec->length) ? -1 : (int)(tablec->capacity - tablec->length);
}
