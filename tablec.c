#include <stdlib.h>
#include <string.h>

#include "tablec.h"

void tablec_init(struct tablec_ht *tablec, size_t max_capacity) {
  tablec->buckets = malloc(sizeof(struct tablec_buckets) * max_capacity);
  tablec->capacity = max_capacity - 1;
  tablec->length = 0;

  while (max_capacity-- != 0) {
    tablec->buckets[max_capacity].nodes = malloc(sizeof(struct tablec_buckets_array));
    tablec->buckets[max_capacity].nodes->key = NULL;
    tablec->buckets[max_capacity].nodes->value = NULL;
    tablec->buckets[max_capacity].length = 0;
    tablec->buckets[max_capacity].nodes->next = NULL;
  }
}

void tablec_resize(struct tablec_ht *tablec, size_t new_max_capacity) {
  /* Tablec_resize is NOT done in this branch, and won't be done if not requested. If you want tablec_resize working on this branch, please open an issue. */
  tablec->capacity = new_max_capacity - 1;
  tablec->buckets = realloc(tablec->buckets, sizeof(struct tablec_buckets) * new_max_capacity);
}

size_t __tablec_hash(struct tablec_ht *tablec, char *key, size_t *size) {
  size_t hash = 0, i = 0;

  while (key[i] != '\0') hash = hash * 37 + (key[i++] & 255);

  *size = i;

  return hash % tablec->capacity;
}

void tablec_set(struct tablec_ht *tablec, char *key, void *value) {
  size_t keyLength;
  size_t hash = __tablec_hash(tablec, key, &keyLength);

  if (tablec->buckets[hash].length == 0) {
    if (tablec->buckets[hash].nodes->key == NULL) {
      tablec->buckets[hash].nodes->key = key;
      tablec->buckets[hash].nodes->value = value;
      tablec->buckets[hash].nodes->length = keyLength;

      tablec->buckets[hash].length++;
      tablec->length++;

      return;
    } else {
      tablec->buckets[hash].nodes->next->key = key;
      tablec->buckets[hash].nodes->next->value = value;
      tablec->buckets[hash].nodes->next->length = keyLength;

      tablec->buckets[hash].length++;
      tablec->length++;

      return;
    }
  } else {
    struct tablec_buckets_array *nodes = tablec->buckets[hash].nodes;

    do {
      if (nodes->key == NULL) {
        nodes->key = key;
        nodes->value = value;
        break;
      }
      nodes = nodes->next;
    } while (nodes != NULL);

    tablec->buckets[hash].length++;
    tablec->length++;

    return;
  }
}

void tablec_del(struct tablec_ht *tablec, char *key) {
  size_t keyLength;
  size_t hash = __tablec_hash(tablec, key, &keyLength);

  if (tablec->buckets[hash].length == 0) {
    tablec->buckets[hash].nodes->key = NULL;
    tablec->buckets[hash].nodes->value = NULL;

    tablec->buckets[hash].length--;
    tablec->length--;

    return;
  } else {
    do {
      if (tablec->buckets[hash].nodes->key != NULL && memcmp(tablec->buckets[hash].nodes->key, key, keyLength) == 0) {
        tablec->buckets[hash].nodes->key = NULL;
        tablec->buckets[hash].nodes->value = NULL;
        break;
      }
    } while (tablec->buckets[hash].nodes->next != NULL);

    tablec->buckets[hash].length--;
    tablec->length--;

    return;
  }
}

void *tablec_get(struct tablec_ht *tablec, char *key) {
  size_t keyLength;
  size_t hash = __tablec_hash(tablec, key, &keyLength);

  struct tablec_buckets_array *nodes = tablec->buckets[hash].nodes;

  if (nodes->key != NULL && memcmp(tablec->buckets[hash].nodes->key, key, keyLength) == 0) {
    return tablec->buckets[hash].nodes->value;
  }

  nodes = tablec->buckets[hash].nodes->next;
  
  while (nodes != NULL) {
    if (nodes->key != NULL && memcmp(nodes->key, key, keyLength) == 0) {
      return nodes->value;
    }
    nodes = nodes->next;
  }

  return NULL;
}

int tablec_full(struct tablec_ht *tablec) {
  return tablec->capacity == tablec->length - 1 ? -1 : tablec->capacity - tablec->length - 1;
}

void tablec_cleanup(struct tablec_ht *tablec) {
  free(tablec->buckets);
  tablec = NULL;
}
