#ifndef TABLEC_H
#define TABLEC_H

struct hashtable_buckets_array {
  char *key;
  void *value;
  size_t length;
  struct hashtable_buckets_array *next;
};

struct hashtable_buckets {
  struct hashtable_buckets_array *nodes;
  size_t length;
};

struct hashtable {
  struct hashtable_buckets *buckets;
  size_t length;
  size_t capacity;
  int secure_mode;
};

void tablec_init(struct hashtable *tablec, size_t max_capacity, int secure_mode);

void tablec_resize(struct hashtable *tablec, size_t new_max_capacity);

void tablec_set(struct hashtable *tablec, char *key, void *value);

void tablec_del(struct hashtable *tablec, char *key);

void *tablec_get(struct hashtable *tablec, char *key);

int tablec_full(struct hashtable *tablec);

void tablec_cleanup(struct hashtable *tablec);

#endif
