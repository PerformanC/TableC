#ifndef TABLEC_H
#define TABLEC_H

struct tablec_buckets_array {
  char *key;
  void *value;
};

struct tablec_buckets {
  struct tablec_buckets_array *array;
  size_t length;
  size_t capacity;
};

struct tablec_ht {
  struct tablec_buckets *buckets;
  size_t length;
  size_t capacity;
};

void tablec_init(struct tablec_ht *tablec, size_t max_capacity);

struct tablec_ht tablec_resize(struct tablec_ht *tablec, size_t new_max_capacity);

void tablec_set(struct tablec_ht *tablec, char *key, void *value);

void tablec_del(struct tablec_ht *tablec, char *key);

void *tablec_get(struct tablec_ht *tablec, char *key);

int tablec_full(struct tablec_ht *tablec);

void tablec_cleanup(struct tablec_ht *tablec);

#endif
