#ifndef TABLEC_H
#define TABLEC_H

struct hashtable_buckets {
  char *key;
  void *value;
};

struct hashtable {
  size_t length;
  size_t capacity;
  struct hashtable_buckets *buckets;
};

void tablec_init(struct hashtable *tablec, size_t max_capacity, int secure_mode);

void tablec_resize(struct hashtable *tablec, size_t new_max_capacity);

void tablec_set(struct hashtable *tablec, char *key, void *value);

void tablec_del(struct hashtable *tablec, char *key);

void *tablec_get(struct hashtable *tablec, char *key);

int tablec_full(struct hashtable *tablec);

void tablec_cleanup(struct hashtable *tablec);

#endif
