#ifndef TABLEC_CA_H
#define TABLEC_CA_H

#include <stddef.h>

struct tablec_ca_bucket {
  char *key;
  void *value;
};

struct tablec_ca_buckets {
  struct tablec_ca_bucket *array;
  size_t length;
  size_t capacity;
};

struct tablec_ca_ht {
  struct tablec_ca_buckets *buckets;
  size_t length;
  size_t capacity;
};

void tablec_ca_init(struct tablec_ca_ht *tablec, size_t max_capacity);

void tablec_ca_resize(struct tablec_ca_ht *tablec, size_t new_max_capacity);

void tablec_ca_set(struct tablec_ca_ht *tablec, char *key, void *value);

struct tablec_ca_bucket *tablec_ca_get(struct tablec_ca_ht *tablec, char *key);

void tablec_ca_del(struct tablec_ca_ht *tablec, char *key);

int tablec_ca_full(struct tablec_ca_ht *tablec);

void tablec_ca_cleanup(struct tablec_ca_ht *tablec);

#endif
