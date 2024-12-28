#ifndef TABLEC_H
#define TABLEC_H

struct tablec_oanm_bucket {
  char *key;
  void *value;
};

struct tablec_oanm_ht {
  size_t length;
  size_t capacity;
  struct tablec_oanm_bucket *buckets;
};

void tablec_oanm_init(struct tablec_oanm_ht *tablec, struct tablec_oanm_bucket buckets[], size_t capacity);

int tablec_oanm_resize(struct tablec_oanm_ht *tablec, struct tablec_oanm_bucket buckets[], size_t new_capacity);

int tablec_oanm_set(struct tablec_oanm_ht *tablec, char *key, void *value);

void tablec_oanm_del(struct tablec_oanm_ht *tablec, char *key);

struct tablec_oanm_bucket *tablec_oanm_get(struct tablec_oanm_ht *tablec, char *key);

size_t tablec_oanm_full(struct tablec_oanm_ht *tablec);

#endif /* TABLEC_H */
