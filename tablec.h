#ifndef TABLEC_OA_H
#define TABLEC_OA_H

struct tablec_oa_bucket {
  char *key;
  void *value;
};

struct tablec_oa_ht {
  size_t length;
  size_t capacity;
  struct tablec_oa_bucket *buckets;
};

void tablec_oa_init(struct tablec_oa_ht *tablec, size_t max_capacity);

void tablec_oa_resize(struct tablec_oa_ht *tablec, size_t new_max_capacity);

void tablec_oa_set(struct tablec_oa_ht *tablec, char *key, void *value);

void tablec_oa_del(struct tablec_oa_ht *tablec, char *key);

struct tablec_oa_bucket *tablec_oa_get(struct tablec_oa_ht *tablec, char *key);

int tablec_oa_full(struct tablec_oa_ht *tablec);

void tablec_oa_cleanup(struct tablec_oa_ht *tablec);

#endif
