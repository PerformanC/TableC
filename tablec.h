#ifndef TABLEC_H
#define TABLEC_H

struct hashtable_buckets_array {
  char *key;
  char *value;
};

struct hashtable_buckets_array_empty {
  size_t index;
  int filled;
};

struct hashtable_buckets {
  struct hashtable_buckets_array *array;
  struct hashtable_buckets_array_empty *emptySlots;
  size_t length;
  size_t capacity;
  size_t emptyCapacity;
};

struct hashtable {
  int secure_mode;
  size_t length;
  size_t capacity;
  struct hashtable_buckets *buckets;
};

void tablec_init(struct hashtable *tablec, size_t max_capacity, int secure_mode);

void tablec_resize(struct hashtable *tablec, size_t new_max_capacity);

void tablec_set(struct hashtable *tablec, char *key, size_t keyLength, void *value);

void tablec_del(struct hashtable *tablec, char *key, size_t keyLength);

void *tablec_get(struct hashtable *tablec, char *key, size_t keyLength);

void tablec_cleanup(struct hashtable *tablec);

#endif
