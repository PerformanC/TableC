#ifndef TABLEC_H
#define TABLEC_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef TABLEC_BUCKET
#error "TABLEC_BUCKET must be defined"
#endif

#ifndef TABLEC_HT
#error "TABLEC_HT must be defined"
#endif

#ifndef TABLEC_BUCKETS
#error "TABLEC_BUCKET must be defined"
#endif

#ifndef TABLEC_KEY_HASH
#error "TABLEC_KEY_HASH must be defined"
#endif

#ifndef TABLEC_KEY
#error "TABLEC_KEY must be defined"
#endif

#ifndef TABLEC_VALUE
#error "TABLEC_VALUE must be defined"
#endif

#ifndef TABLEC_KEY_COMPARE
#error "TABLEC_KEY_COMPARE must be defined"
#endif

#ifndef TABLEC_CHECK_NULL
#error "TABLEC_CHECK_NULL must be defined"
#endif

size_t _tablec_hash(void *_key, void *_data) {
  TABLEC_KEY_HASH(_key, _data);
}

int _tablec_compare(TABLEC_BUCKET *bucket, void *_key, void *_data) {
  TABLEC_KEY_COMPARE(bucket->TABLEC_KEY, _key, _data);
}

void tablec_init(TABLEC_HT *tablec, TABLEC_BUCKET *buckets, size_t capacity) {
  tablec->length = 0;
  tablec->capacity = capacity;
  tablec->TABLEC_BUCKETS = buckets;

  memset(tablec->TABLEC_BUCKETS, 0, sizeof(TABLEC_BUCKET) * capacity);
}

int tablec_resize(TABLEC_HT *tablec, TABLEC_BUCKET *new_buckets, size_t new_capacity, void *data) {
  size_t old_capacity = tablec->capacity;
  size_t hash;

  tablec->capacity = new_capacity;

  memset(new_buckets, 0, sizeof(TABLEC_BUCKET) * new_capacity);

  while (old_capacity--) {
    if (TABLEC_CHECK_NULL(tablec->TABLEC_BUCKETS[old_capacity].TABLEC_KEY)) continue;

    hash = _tablec_hash(&tablec->TABLEC_BUCKETS[old_capacity].TABLEC_KEY, data) % new_capacity;

    if (TABLEC_CHECK_NULL(new_buckets[hash].TABLEC_KEY)) {
      new_buckets[hash].TABLEC_KEY = tablec->TABLEC_BUCKETS[old_capacity].TABLEC_KEY;
      new_buckets[hash].TABLEC_VALUE = tablec->TABLEC_BUCKETS[old_capacity].TABLEC_VALUE;

      continue;
    }

    while (!(TABLEC_CHECK_NULL(new_buckets[hash].TABLEC_KEY)) && (hash < tablec->capacity)) ++hash;

    if (hash == tablec->capacity) return -1;

    if (TABLEC_CHECK_NULL(new_buckets[hash].TABLEC_KEY)) {
      new_buckets[hash].TABLEC_KEY = tablec->TABLEC_BUCKETS[old_capacity].TABLEC_KEY;
      new_buckets[hash].TABLEC_VALUE = tablec->TABLEC_BUCKETS[old_capacity].TABLEC_VALUE;
    }
  }

  tablec->TABLEC_BUCKETS = new_buckets;

  return 0;
}

int tablec_set(TABLEC_HT *tablec, void *key, void *value, void *data) {
  size_t hash;

  if ((tablec->length - 1) == tablec->capacity) return -1;

  hash = _tablec_hash(key, data) % tablec->capacity;

  while (hash != tablec->capacity) {
    if (TABLEC_CHECK_NULL(tablec->TABLEC_BUCKETS[hash].TABLEC_KEY)) {
      TABLEC_ASSIGN(&tablec->TABLEC_BUCKETS[hash].TABLEC_KEY, key);
      TABLEC_ASSIGN(&tablec->TABLEC_BUCKETS[hash].TABLEC_VALUE, value);

      ++tablec->length;

      return tablec->capacity - tablec->length + 1;
    }

    ++hash;
  }

  return -1;
}

void tablec_del(TABLEC_HT *tablec, void *key, void *data) {
  size_t hash = _tablec_hash(key, data) % tablec->capacity;

  while (hash != tablec->capacity) {
    if (!(TABLEC_CHECK_NULL(tablec->TABLEC_BUCKETS[hash].TABLEC_KEY)) && _tablec_compare(&tablec->TABLEC_BUCKETS[hash], key, data) == 0) {
      TABLEC_ASSIGN(&tablec->TABLEC_BUCKETS[hash].TABLEC_KEY, NULL);
      TABLEC_ASSIGN(&tablec->TABLEC_BUCKETS[hash].TABLEC_VALUE, NULL);

      tablec->length--;

      return;
    }

    ++hash;
  }
}

TABLEC_BUCKET *tablec_get(TABLEC_HT *tablec, void *key, void *data) {
  size_t hash = _tablec_hash(key, data) % tablec->capacity;

  while (hash != tablec->capacity) {
    if (!(TABLEC_CHECK_NULL(tablec->TABLEC_BUCKETS[hash].TABLEC_KEY)) && _tablec_compare(&tablec->TABLEC_BUCKETS[hash], key, data) == 0)
      return &tablec->TABLEC_BUCKETS[hash];

    ++hash;
  }

  return NULL;
}

int tablec_full(TABLEC_HT *tablec) {
  return tablec->capacity == tablec->length ? -1 : tablec->capacity - tablec->length;
}

#ifdef __cplusplus
}

#endif

#endif /* TABLEC_H */
