#ifndef TABLEC_OAC_H
#define TABLEC_OAC_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef TABLEC_OAC_SYMBOL_BUCKET
#error "TABLEC_OAC_SYMBOL_BUCKET must be defined"
#endif

#ifndef TABLEC_OAC_SYMBOL_HT
#error "TABLEC_OAC_SYMBOL_HT must be defined"
#endif

#ifndef TABLEC_OAC_SYMBOL_BUCKETS
#error "TABLEC_OAC_SYMBOL_BUCKET must be defined"
#endif

#ifndef TABLEC_OAC_SYMBOL_KEY_HASH
#error "TABLEC_OAC_SYMBOL_KEY_HASH must be defined"
#endif

#ifndef TABLEC_OAC_SYMBOL_KEY
#error "TABLEC_OAC_SYMBOL_KEY must be defined"
#endif

#ifndef TABLEC_OAC_SYMBOL_VALUE
#error "TABLEC_OAC_SYMBOL_VALUE must be defined"
#endif

#ifndef TABLEC_OAC_SYMBOL_ASSIGN
#error "TABLEC_OAC_SYMBOL_ASSIGN must be defined"
#endif

#ifndef TABLEC_OAC_SYMBOL_KEY_COMPARE
#error "TABLEC_OAC_SYMBOL_KEY_COMPARE must be defined"
#endif

#ifndef TABLEC_OAC_SYMBOL_CHECK_NULL
#error "TABLEC_OAC_SYMBOL_CHECK_NULL must be defined"
#endif

size_t _tablec_oac_hash(void *_key, void *_data) {
  TABLEC_OAC_SYMBOL_KEY_HASH(_key, _data);
}

int _tablec_oac_compare(TABLEC_OAC_SYMBOL_BUCKET *bucket, void *_key, void *_data) {
  TABLEC_OAC_SYMBOL_KEY_COMPARE(bucket->TABLEC_OAC_SYMBOL_KEY, _key, _data);
}

void tablec_oac_init(TABLEC_OAC_SYMBOL_HT *tablec, TABLEC_OAC_SYMBOL_BUCKET *buckets, size_t capacity) {
  tablec->length = 0;
  tablec->capacity = capacity;
  tablec->TABLEC_OAC_SYMBOL_BUCKETS = buckets;

  memset(tablec->TABLEC_OAC_SYMBOL_BUCKETS, 0, sizeof(TABLEC_OAC_SYMBOL_BUCKET) * capacity);
}

int tablec_oac_resize(TABLEC_OAC_SYMBOL_HT *tablec, TABLEC_OAC_SYMBOL_BUCKET *new_buckets, size_t new_capacity, void *data) {
  size_t old_capacity = tablec->capacity;
  size_t hash;

  tablec->capacity = new_capacity;

  memset(new_buckets, 0, sizeof(TABLEC_OAC_SYMBOL_BUCKET) * new_capacity);

  while (old_capacity--) {
    if (TABLEC_OAC_SYMBOL_CHECK_NULL(tablec->TABLEC_OAC_SYMBOL_BUCKETS[old_capacity].TABLEC_OAC_SYMBOL_KEY)) continue;

    hash = _tablec_oac_hash(&tablec->TABLEC_OAC_SYMBOL_BUCKETS[old_capacity].TABLEC_OAC_SYMBOL_KEY, data) % new_capacity;

    if (TABLEC_OAC_SYMBOL_CHECK_NULL(new_buckets[hash].TABLEC_OAC_SYMBOL_KEY)) {
      new_buckets[hash].TABLEC_OAC_SYMBOL_KEY = tablec->TABLEC_OAC_SYMBOL_BUCKETS[old_capacity].TABLEC_OAC_SYMBOL_KEY;
      new_buckets[hash].TABLEC_OAC_SYMBOL_VALUE = tablec->TABLEC_OAC_SYMBOL_BUCKETS[old_capacity].TABLEC_OAC_SYMBOL_VALUE;

      continue;
    }

    while (!(TABLEC_OAC_SYMBOL_CHECK_NULL(new_buckets[hash].TABLEC_OAC_SYMBOL_KEY)) && (hash < tablec->capacity)) hash++;

    if (hash == tablec->capacity) return -1;

    if (TABLEC_OAC_SYMBOL_CHECK_NULL(new_buckets[hash].TABLEC_OAC_SYMBOL_KEY)) {
      new_buckets[hash].TABLEC_OAC_SYMBOL_KEY = tablec->TABLEC_OAC_SYMBOL_BUCKETS[old_capacity].TABLEC_OAC_SYMBOL_KEY;
      new_buckets[hash].TABLEC_OAC_SYMBOL_VALUE = tablec->TABLEC_OAC_SYMBOL_BUCKETS[old_capacity].TABLEC_OAC_SYMBOL_VALUE;
    }
  }

  tablec->TABLEC_OAC_SYMBOL_BUCKETS = new_buckets;

  return 0;
}

int tablec_oac_set(TABLEC_OAC_SYMBOL_HT *tablec, void *key, void *value, void *data) {
  size_t hash;

  if ((tablec->length - 1) == tablec->capacity) return -1;

  hash = _tablec_oac_hash(key, data) % tablec->capacity;

  while (hash != tablec->capacity) {
    if (TABLEC_OAC_SYMBOL_CHECK_NULL(tablec->TABLEC_OAC_SYMBOL_BUCKETS[hash].TABLEC_OAC_SYMBOL_KEY)) {
      TABLEC_OAC_SYMBOL_ASSIGN(&tablec->TABLEC_OAC_SYMBOL_BUCKETS[hash].TABLEC_OAC_SYMBOL_KEY, key);
      TABLEC_OAC_SYMBOL_ASSIGN(&tablec->TABLEC_OAC_SYMBOL_BUCKETS[hash].TABLEC_OAC_SYMBOL_VALUE, value);

      tablec->length++;

      return tablec->capacity - tablec->length + 1;
    }

    hash++;
  }

  return -1;
}

void tablec_oac_del(TABLEC_OAC_SYMBOL_HT *tablec, void *key, void *data) {
  size_t hash = _tablec_oac_hash(key, data) % tablec->capacity;

  while (hash != tablec->capacity) {
    if (!(TABLEC_OAC_SYMBOL_CHECK_NULL(tablec->TABLEC_OAC_SYMBOL_BUCKETS[hash].TABLEC_OAC_SYMBOL_KEY)) && _tablec_oac_compare(&tablec->TABLEC_OAC_SYMBOL_BUCKETS[hash], key, data) == 0) {
      TABLEC_OAC_SYMBOL_ASSIGN(&tablec->TABLEC_OAC_SYMBOL_BUCKETS[hash].TABLEC_OAC_SYMBOL_KEY, NULL);
      TABLEC_OAC_SYMBOL_ASSIGN(&tablec->TABLEC_OAC_SYMBOL_BUCKETS[hash].TABLEC_OAC_SYMBOL_VALUE, NULL);

      tablec->length--;

      return;
    }

    hash++;
  }
}

TABLEC_OAC_SYMBOL_BUCKET *tablec_oac_get(TABLEC_OAC_SYMBOL_HT *tablec, void *key, void *data) {
  size_t hash = _tablec_oac_hash(key, data) % tablec->capacity;

  while (hash != tablec->capacity) {
    if (!(TABLEC_OAC_SYMBOL_CHECK_NULL(tablec->TABLEC_OAC_SYMBOL_BUCKETS[hash].TABLEC_OAC_SYMBOL_KEY)) && _tablec_oac_compare(&tablec->TABLEC_OAC_SYMBOL_BUCKETS[hash], key, data) == 0)
      return &tablec->TABLEC_OAC_SYMBOL_BUCKETS[hash];

    hash++;
  }

  return NULL;
}

int tablec_oac_full(TABLEC_OAC_SYMBOL_HT *tablec) {
  return (int)(tablec->capacity == tablec->length) ? -1 : (int)(tablec->capacity - tablec->length);
}

#ifdef __cplusplus
}

#endif

#endif /* TABLEC_OAC_H */
