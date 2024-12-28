#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tablec.h"

void tablec_oa_init(struct tablec_oa_ht *tablec, size_t max_capacity) {
  tablec->length = 0;
  tablec->capacity = max_capacity;
  tablec->buckets = calloc(sizeof(struct tablec_oa_bucket) * max_capacity, 1);
}

static size_t __tablec_oa_hash(struct tablec_oa_ht *tablec, char *key) {
  size_t hash = 0, i = 0;

  while (key[i] != '\0') hash = hash * 37 + (key[i++] & 255);

  return hash % tablec->capacity;
}

void tablec_oa_resize(struct tablec_oa_ht *tablec, size_t new_max_capacity) {
  struct tablec_oa_ht newHashtable;
  tablec_oa_init(&newHashtable, new_max_capacity);

  while (tablec->capacity--) {
    if (!tablec->buckets[tablec->capacity].key) continue;
      
    tablec_oa_set(&newHashtable, tablec->buckets[tablec->capacity].key, tablec->buckets[tablec->capacity].value);
  }

  tablec_oa_cleanup(tablec);
  *tablec = newHashtable;
}

void tablec_oa_set(struct tablec_oa_ht *tablec, char *key, void *value) {
  size_t hash;

  if (tablec->length - 1 == tablec->capacity) tablec_oa_resize(tablec, tablec->capacity * 2);

  hash = __tablec_oa_hash(tablec, key);

  while (hash != tablec->capacity) {
    if (!tablec->buckets[hash].key) {
      tablec->buckets[hash].key = key;
      tablec->buckets[hash].value = value;

      tablec->length++;

      return;
    }

    hash++;
  }

  tablec_oa_resize(tablec, tablec->capacity * 2);
  tablec_oa_set(tablec, key, value);

  return;
}

void tablec_oa_del(struct tablec_oa_ht *tablec, char *key) {
  size_t hash = __tablec_oa_hash(tablec, key);

  while (hash != tablec->capacity) {
    if (tablec->buckets[hash].key && strcmp(tablec->buckets[hash].key, key) == 0) {
      tablec->buckets[hash].key = NULL;
      tablec->buckets[hash].value = NULL;

      tablec->length--;

      return;
    }

    hash++;
  }
}

struct tablec_oa_bucket *tablec_oa_get(struct tablec_oa_ht *tablec, char *key) {
  size_t hash = __tablec_oa_hash(tablec, key);

  while (hash != tablec->capacity) {
    if (tablec->buckets[hash].key && strcmp(tablec->buckets[hash].key, key) == 0)
      return &tablec->buckets[hash];

    hash++;
  }

  return NULL;
}

int tablec_oa_full(struct tablec_oa_ht *tablec) {
  return tablec->capacity == tablec->length ? -1 : tablec->capacity - tablec->length;
}

void tablec_oa_cleanup(struct tablec_oa_ht *tablec) {
  free(tablec->buckets);
}
