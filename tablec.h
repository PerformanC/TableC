#ifndef TABLEC_H
#define TABLEC_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef TABLEC_SYMBOL_BUCKET
#error "TABLEC_SYMBOL_BUCKET must be defined"
#endif

#ifndef TABLEC_SYMBOL_HT
#error "TABLEC_SYMBOL_HT must be defined"
#endif

#ifndef TABLEC_SYMBOL_BUCKETS
#error "TABLEC_SYMBOL_BUCKET must be defined"
#endif

#ifndef TABLEC_SYMBOL_KEY_HASH
#error "TABLEC_SYMBOL_KEY_HASH must be defined"
#endif

#ifndef TABLEC_SYMBOL_KEY
#error "TABLEC_SYMBOL_KEY must be defined"
#endif

#ifndef TABLEC_SYMBOL_VALUE
#error "TABLEC_SYMBOL_VALUE must be defined"
#endif

#ifndef TABLEC_SYMBOL_ASSIGN
#error "TABLEC_SYMBOL_ASSIGN must be defined"
#endif

#ifndef TABLEC_SYMBOL_KEY_COMPARE
#error "TABLEC_SYMBOL_KEY_COMPARE must be defined"
#endif

#ifndef TABLEC_SYMBOL_CHECK_NULL
#error "TABLEC_SYMBOL_CHECK_NULL must be defined"
#endif

size_t _tablec_hash(void *_key, void *_data) {
  TABLEC_SYMBOL_KEY_HASH(_key, _data);
}

int _tablec_compare(TABLEC_SYMBOL_BUCKET *bucket, void *_key, void *_data) {
  TABLEC_SYMBOL_KEY_COMPARE(bucket->TABLEC_SYMBOL_KEY, _key, _data);
}

void tablec_init(TABLEC_SYMBOL_HT *tablec, TABLEC_SYMBOL_BUCKET *buckets, size_t capacity) {
  tablec->length = 0;
  tablec->capacity = capacity;
  tablec->TABLEC_SYMBOL_BUCKETS = buckets;

  memset(tablec->TABLEC_SYMBOL_BUCKETS, 0, sizeof(TABLEC_SYMBOL_BUCKET) * capacity);
}

int tablec_resize(TABLEC_SYMBOL_HT *tablec, TABLEC_SYMBOL_BUCKET *new_buckets, size_t new_capacity, void *data) {
  size_t old_capacity = tablec->capacity;
  size_t hash;

  tablec->capacity = new_capacity;

  memset(new_buckets, 0, sizeof(TABLEC_SYMBOL_BUCKET) * new_capacity);

  while (old_capacity--) {
    if (TABLEC_SYMBOL_CHECK_NULL(tablec->TABLEC_SYMBOL_BUCKETS[old_capacity].TABLEC_SYMBOL_KEY)) continue;

    hash = _tablec_hash(&tablec->TABLEC_SYMBOL_BUCKETS[old_capacity].TABLEC_SYMBOL_KEY, data) % new_capacity;

    if (TABLEC_SYMBOL_CHECK_NULL(new_buckets[hash].TABLEC_SYMBOL_KEY)) {
      new_buckets[hash].TABLEC_SYMBOL_KEY = tablec->TABLEC_SYMBOL_BUCKETS[old_capacity].TABLEC_SYMBOL_KEY;
      new_buckets[hash].TABLEC_SYMBOL_VALUE = tablec->TABLEC_SYMBOL_BUCKETS[old_capacity].TABLEC_SYMBOL_VALUE;

      continue;
    }

    while (!(TABLEC_SYMBOL_CHECK_NULL(new_buckets[hash].TABLEC_SYMBOL_KEY)) && (hash < tablec->capacity)) hash++;

    if (hash == tablec->capacity) return -1;

    if (TABLEC_SYMBOL_CHECK_NULL(new_buckets[hash].TABLEC_SYMBOL_KEY)) {
      new_buckets[hash].TABLEC_SYMBOL_KEY = tablec->TABLEC_SYMBOL_BUCKETS[old_capacity].TABLEC_SYMBOL_KEY;
      new_buckets[hash].TABLEC_SYMBOL_VALUE = tablec->TABLEC_SYMBOL_BUCKETS[old_capacity].TABLEC_SYMBOL_VALUE;
    }
  }

  tablec->TABLEC_SYMBOL_BUCKETS = new_buckets;

  return 0;
}

int tablec_set(TABLEC_SYMBOL_HT *tablec, void *key, void *value, void *data) {
  size_t hash;

  if ((tablec->length - 1) == tablec->capacity) return -1;

  hash = _tablec_hash(key, data) % tablec->capacity;

  while (hash != tablec->capacity) {
    if (TABLEC_SYMBOL_CHECK_NULL(tablec->TABLEC_SYMBOL_BUCKETS[hash].TABLEC_SYMBOL_KEY)) {
      TABLEC_SYMBOL_ASSIGN(&tablec->TABLEC_SYMBOL_BUCKETS[hash].TABLEC_SYMBOL_KEY, key);
      TABLEC_SYMBOL_ASSIGN(&tablec->TABLEC_SYMBOL_BUCKETS[hash].TABLEC_SYMBOL_VALUE, value);

      tablec->length++;

      return tablec->capacity - tablec->length + 1;
    }

    hash++;
  }

  return -1;
}

void tablec_del(TABLEC_SYMBOL_HT *tablec, void *key, void *data) {
  size_t hash = _tablec_hash(key, data) % tablec->capacity;

  while (hash != tablec->capacity) {
    if (!(TABLEC_SYMBOL_CHECK_NULL(tablec->TABLEC_SYMBOL_BUCKETS[hash].TABLEC_SYMBOL_KEY)) && _tablec_compare(&tablec->TABLEC_SYMBOL_BUCKETS[hash], key, data) == 0) {
      TABLEC_SYMBOL_ASSIGN(&tablec->TABLEC_SYMBOL_BUCKETS[hash].TABLEC_SYMBOL_KEY, NULL);
      TABLEC_SYMBOL_ASSIGN(&tablec->TABLEC_SYMBOL_BUCKETS[hash].TABLEC_SYMBOL_VALUE, NULL);

      tablec->length--;

      return;
    }

    hash++;
  }
}

TABLEC_SYMBOL_BUCKET *tablec_get(TABLEC_SYMBOL_HT *tablec, void *key, void *data) {
  size_t hash = _tablec_hash(key, data) % tablec->capacity;

  while (hash != tablec->capacity) {
    if (!(TABLEC_SYMBOL_CHECK_NULL(tablec->TABLEC_SYMBOL_BUCKETS[hash].TABLEC_SYMBOL_KEY)) && _tablec_compare(&tablec->TABLEC_SYMBOL_BUCKETS[hash], key, data) == 0)
      return &tablec->TABLEC_SYMBOL_BUCKETS[hash];

    hash++;
  }

  return NULL;
}

int tablec_full(TABLEC_SYMBOL_HT *tablec) {
  return (int)(tablec->capacity == tablec->length) ? -1 : (int)(tablec->capacity - tablec->length);
}

#ifdef __cplusplus
}

#endif

#endif /* TABLEC_H */
