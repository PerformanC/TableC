#ifndef TABLEC_H
#define TABLEC_H

struct hashtable_buckets {
  char *key;
  char *value;
};

struct hashtable {
  size_t max_capacity;
  struct hashtable_buckets *buckets;
};

void tablec_init(struct hashtable *tablec, int max_capacity);

size_t __tablec_mkIndex(struct hashtable *tablec, char *key);

void tablec_set(struct hashtable *tablec, char *key, char *value);

void tablec_del(struct hashtable *tablec, char *key);

char *tablec_get(struct hashtable *tablec, char *key);

void tablec_cleanup(struct hashtable *tablec);

#endif
