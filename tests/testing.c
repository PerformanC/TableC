/*
  Testing special cases of TableC. This file is NOT a part of the TableC library. It is only used to test the library behaviour in special situations.

  This file can't be copied, modified or redistributed without the author's permission. But can be used as a reference for your own projects, and also can be used to test your own implementations of TableC, especially while making PRs for it.
  Author: @ThePedroo
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <assert.h>

struct tablec_oac_bucket {
  char *key;
  void *value;
};

struct tablec_oac_ht {
  size_t length;
  size_t capacity;
  struct tablec_oac_bucket *buckets;
};

#define TABLEC_OAC_SYMBOL_BUCKET struct tablec_oac_bucket

#define TABLEC_OAC_SYMBOL_HT struct tablec_oac_ht

#define TABLEC_OAC_SYMBOL_BUCKETS buckets

#define TABLEC_OAC_SYMBOL_KEY_HASH(_key, data)                    \
  size_t hash = 0, i = 0;                                     \
  char *key = (char *)_key;                                   \
                                                              \
  (void)data;                                                 \
                                                              \
  while (key[i] != '\0') hash = hash * 37 + (key[i++] & 255); \
                                                              \
  return hash;

#define TABLEC_OAC_SYMBOL_KEY key

#define TABLEC_OAC_SYMBOL_VALUE value

#define TABLEC_OAC_SYMBOL_KEY_COMPARE(key, otherKey, data) \
    (void)data;                                        \
                                                       \
    return strcmp(key, otherKey)

#define TABLEC_OAC_SYMBOL_CHECK_NULL(x) (x == NULL)

#define TABLEC_OAC_SYMBOL_ASSIGN(x, y) *x = y

#include "greatest.h"
#include "../tablec.h"

char *key = "hello";
char *otherKey = "8";
char *value = "Funcionando, 1, 2 e 3..";

TEST start_hashtable(void) {
  struct tablec_oac_ht tablec;
  struct tablec_oac_bucket buckets[16];
  tablec_oac_init(&tablec, buckets, 16);

  PASSm("TableC was able to initialize the hashtable.");
}

TEST setting_key(void) {
  struct tablec_oac_ht tablec;
  struct tablec_oac_bucket buckets[16];
  tablec_oac_init(&tablec, buckets, 16);

  tablec_oac_set(&tablec, key, value, NULL);
  ASSERT_EQm("TableC was not able to set a key and a value.", strcmp((char *)tablec_oac_get(&tablec, key, NULL)->value, value), 0);

  PASSm("TableC was able to set a key and a value.");
}

TEST setting_key_and_read_after_deleting(void) {
  struct tablec_oac_ht tablec;
  struct tablec_oac_bucket buckets[16];
  tablec_oac_init(&tablec, buckets, 16);

  tablec_oac_set(&tablec, key, value, NULL);
  ASSERT_EQm("TableC was not able to set a key and a value.", strcmp((char *)tablec_oac_get(&tablec, key, NULL)->value, value), 0);

  tablec_oac_del(&tablec, key, NULL);
  ASSERT_EQm("TableC was not able to delete key.", tablec_oac_get(&tablec, key, NULL) == NULL ? 0 : 1, 0);

  tablec_oac_set(&tablec, key, value, NULL);
  ASSERT_EQm("TableC was not able to set a key and a value.", strcmp((char *)tablec_oac_get(&tablec, key, NULL)->value, value), 0);

  PASSm("TableC was able to set a key and a value after deleting the same key.");
}

TEST hashtable_overflow(void) {
  struct tablec_oac_ht tablec;
  struct tablec_oac_bucket buckets[1];
  tablec_oac_init(&tablec, buckets, 1);

  ASSERT_EQm("TableC was not able to detect that the hashtable is full.", tablec_oac_full(&tablec), 1);

  tablec_oac_set(&tablec, key, value, NULL);
  ASSERT_EQm("TableC was not able to set a key and a value.", strcmp((char *)tablec_oac_get(&tablec, key, NULL)->value, value), 0);

  tablec_oac_set(&tablec, otherKey, value, NULL);
  ASSERT_EQm("TableC was not able to set a key and a value.", tablec_oac_get(&tablec, otherKey, NULL) == NULL, 1);

  ASSERT_EQm("TableC was not able to detect that the hashtable is full.", tablec_oac_full(&tablec), -1);

  PASSm("TableC was able to overflow the hashtable.");
}

TEST setting_2_keys_with_the_same_pos_and_deleting(void) {
  struct tablec_oac_ht tablec;
  struct tablec_oac_bucket buckets[100];
  tablec_oac_init(&tablec, buckets, 100);

  tablec_oac_set(&tablec, key, value, NULL);
  ASSERT_EQm("TableC was not able to set a key and a value.", strcmp((char *)tablec_oac_get(&tablec, key, NULL)->value, value), 0);

  tablec_oac_set(&tablec, otherKey, value, NULL);
  ASSERT_EQm("TableC was not able to set a key and a value.", strcmp((char *)tablec_oac_get(&tablec, otherKey, NULL)->value, value), 0);

  tablec_oac_del(&tablec, key, NULL);
  ASSERT_EQm("TableC was not able to delete key.", tablec_oac_get(&tablec, key, NULL) == NULL ? 0 : 1, 0);

  tablec_oac_set(&tablec, key, value, NULL);
  ASSERT_EQm("TableC was not able to set a key and a value.", strcmp((char *)tablec_oac_get(&tablec, key, NULL)->value, value), 0);

  PASSm("TableC was able to set a key and a value after deleting the same key.");
}

TEST deleting_and_reading_non_exist_key(void) {
  struct tablec_oac_ht tablec;
  struct tablec_oac_bucket buckets[16];
  tablec_oac_init(&tablec, buckets, 16);

  tablec_oac_del(&tablec, key, NULL);
  ASSERT_EQm("TableC was not able to delete key.", tablec_oac_get(&tablec, key, NULL) == NULL ? 0 : 1, 0);

  PASSm("TableC was able to delete a non existent key and not segfault.");
}

TEST see_empty_slots_after_deleting(void) {
  struct tablec_oac_ht tablec;
  struct tablec_oac_bucket buckets[100];
  tablec_oac_init(&tablec, buckets, 100);

  tablec_oac_set(&tablec, key, value, NULL);
  ASSERT_EQm("TableC was not able to set a key and a value.", strcmp((char *)tablec_oac_get(&tablec, key, NULL)->value, value), 0);

  tablec_oac_set(&tablec, otherKey, value, NULL);
  ASSERT_EQm("TableC was not able to set a key and a value.", strcmp((char *)tablec_oac_get(&tablec, otherKey, NULL)->value, value), 0);

  tablec_oac_del(&tablec, key, NULL);
  ASSERT_EQm("TableC was not able to delete key.", tablec_oac_get(&tablec, key, NULL) == NULL, 1);

  PASSm("TableC was able to add the empty slot index to the empty slots array (successful deletion).");
}

TEST test_resize(void) {
  char keyRandom[1000];
  size_t i = 0;
  struct tablec_oac_bucket buckets[100];
  struct tablec_oac_bucket buckets2[1000];

  struct tablec_oac_ht tablec;
  tablec_oac_init(&tablec, buckets, 100);

  while(i++ < 1000) {
    sprintf(keyRandom, "%zu", i);
    tablec_oac_resize(&tablec, buckets2, tablec.capacity + 1, NULL);
    tablec_oac_set(&tablec, keyRandom, value, NULL);
    ASSERT_EQm("TableC was not able to set a key and a value.", strcmp((char *)tablec_oac_get(&tablec, keyRandom, NULL)->value, value), 0);
  }

  PASSm("TableC was able to resize the hashtable.");
}

TEST mini_fuzz_testing(void) {
  char keyRandom[1000];
  size_t i = 0;

  struct tablec_oac_ht tablec;
  struct tablec_oac_bucket buckets[1000];
  tablec_oac_init(&tablec, buckets, 1000);

  while(i++ < 1000) {
    sprintf(keyRandom, "%d", rand() % 1000);
    tablec_oac_set(&tablec, keyRandom, value, NULL);
    ASSERT_EQm("TableC was not able to set a key and a value.", strcmp((char *)tablec_oac_get(&tablec, keyRandom, NULL)->value, value), 0);
  }

  PASSm("TableC was able to pass the mini fuzzy testing.");
}

SUITE(special_cases) {
  RUN_TEST(start_hashtable);
  RUN_TEST(setting_key);
  RUN_TEST(setting_key_and_read_after_deleting);
  RUN_TEST(hashtable_overflow);
  RUN_TEST(setting_2_keys_with_the_same_pos_and_deleting);
  RUN_TEST(deleting_and_reading_non_exist_key);
  RUN_TEST(see_empty_slots_after_deleting);
  RUN_TEST(test_resize);
  RUN_TEST(mini_fuzz_testing);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();

  RUN_SUITE(special_cases);

  GREATEST_MAIN_END();

  return 0;
}
