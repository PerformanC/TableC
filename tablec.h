#ifndef TABLEC_H
#define TABLEC_H

struct tablec_bucket {
  char *key;
  void *value;
};

struct tablec_ht {
  size_t length;
  size_t capacity;
  struct tablec_bucket *buckets;
};

void tablec_init(struct tablec_ht *tablec, struct tablec_bucket buckets[], size_t capacity);

int tablec_resize(struct tablec_ht *tablec, struct tablec_bucket buckets[], size_t new_capacity);

int tablec_set(struct tablec_ht *tablec, char *key, void *value);

void tablec_del(struct tablec_ht *tablec, char *key);

struct tablec_bucket *tablec_get(struct tablec_ht *tablec, char *key);

size_t tablec_full(struct tablec_ht *tablec);

#endif /* TABLEC_H */
