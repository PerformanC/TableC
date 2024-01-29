#ifndef TABLEC_H
#define TABLEC_H

#include <stddef.h>

struct tablec_bucket {
  char *key;
  void *value;
};

struct tablec_buckets {
  struct tablec_bucket *array;
  size_t length;
  size_t capacity;
};

struct tablec_ht {
  struct tablec_buckets *buckets;
  size_t length;
  size_t capacity;
};

void tablec_init(struct tablec_ht *tablec, size_t max_capacity);

void tablec_resize(struct tablec_ht *tablec, size_t new_max_capacity);

void tablec_set(struct tablec_ht *tablec, char *key, void *value);

struct tablec_bucket tablec_get(struct tablec_ht *tablec, char *key);

void tablec_del(struct tablec_ht *tablec, char *key);

int tablec_full(struct tablec_ht *tablec);

void tablec_cleanup(struct tablec_ht *tablec);

#endif
