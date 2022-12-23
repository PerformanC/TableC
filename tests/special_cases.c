/*
  Testing special cases of TableC. This file is NOT a part of the TableC library. It is only used to test the library behaviour in special situations.

  This file can't be copied, modified or redistributed without the author's permission. But can be used as a reference for your own projects, and also can be used to test your own implementations of TableC, especially while making PRs for it.
  Author: @ThePedroo
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include "greatest.h"
#include "../tablec.h"

char *key = "Hello";
char *value = "Funcionando, 1, 2 e 3..";

TEST start_hashtable(void) {
  struct hashtable tablec;
  tablec_init(&tablec, 16, 1);
  ASSERT_EQm("TableC was not able to initialize the hashtable.", tablec.capacity, (size_t)16);

  tablec_cleanup(&tablec);

  PASSm("TableC was able to initialize the hashtable.");
}

TEST setting_key(void) {
  struct hashtable tablec;
  tablec_init(&tablec, 16, 1);
  ASSERT_EQm("TableC was not able to initialize.", tablec.capacity, (size_t)16);

  tablec_set(&tablec, key, 0, value);
  ASSERT_EQm("TableC was not able to set a key and a value.", strcmp(tablec_get(&tablec, key, 0), value), 0);

  tablec_cleanup(&tablec);

  PASSm("TableC was able to set a key and a value.");
}

TEST setting_key_and_read_after_deleting(void) {
  struct hashtable tablec;
  tablec_init(&tablec, 16, 1);
  ASSERT_EQm("TableC was not able to initialize.", tablec.capacity, (size_t)16);

  tablec_set(&tablec, key, 0, value);
  ASSERT_EQm("TableC was not able to set a key and a value.", strcmp(tablec_get(&tablec, key, 0), value), 0);

  tablec_del(&tablec, key, 0);
  ASSERT_EQm("TableC was not able to delete key.", tablec_get(&tablec, key, 0) == NULL ? 0 : 1, 0);

  tablec_set(&tablec, key, 0, value);
  ASSERT_EQm("TableC was not able to set a key and a value.", strcmp(tablec_get(&tablec, key, 0), value), 0);

  tablec_cleanup(&tablec);

  PASSm("TableC was able to set a key and a value after deleting the same key.");
}

TEST deleting_and_reading_non_exist_key(void) {
  struct hashtable tablec;
  tablec_init(&tablec, 16, 1);
  ASSERT_EQm("TableC was not able to initialize.", tablec.capacity, (size_t)16);

  tablec_del(&tablec, key, 0);
  ASSERT_EQm("TableC was not able to delete key.", tablec_get(&tablec, key, 0) == NULL ? 0 : 1, 0);

  tablec_cleanup(&tablec);

  PASSm("TableC was able to delete a non existent key and not segfault.");
}

TEST see_empty_slots_after_deleting(void) {
  struct hashtable tablec;
  tablec_init(&tablec, 16, 1);
  ASSERT_EQm("TableC was not able to initialize.", tablec.capacity, (size_t)16);

  tablec_set(&tablec, key, 0, value);
  ASSERT_EQm("TableC was not able to set a key and a value.", strcmp(tablec_get(&tablec, key, 0), value), 0);

  tablec_set(&tablec, key, 0, value);
  ASSERT_EQm("TableC was not able to set a key and a value.", strcmp(tablec_get(&tablec, key, 0), value), 0);

  tablec_del(&tablec, key, 0);
  ASSERT_EQm("TableC was not able to add the empty slot index to the empty slots array.", tablec.buckets[0].emptySlots[0].filled, 1);

  tablec_cleanup(&tablec);

  PASSm("TableC was able to add the empty slot index to the empty slots array (successful deletion).");
}

TEST mini_fuzzy_testing(void) {
  struct hashtable tablec;
  tablec_init(&tablec, 1000, 0);
  ASSERT_EQm("TableC was not able to initialize.", tablec.capacity, (size_t)1000);

  char keyRandom[100];
  size_t i = 0;
  while(i < 1000) {
    sprintf(keyRandom, "%d", rand() % 1000);
    tablec_set(&tablec, keyRandom, 0, value);
    ASSERT_EQm("TableC was not able to set a key and a value.", strcmp(tablec_get(&tablec, keyRandom, 0), value), 0);
    i++;
  }

  tablec_cleanup(&tablec);

  PASSm("TableC was able to pass the mini fuzzy testing.");
}

SUITE(special_cases) {
  RUN_TEST(start_hashtable);
  RUN_TEST(setting_key);
  RUN_TEST(setting_key_and_read_after_deleting);
  RUN_TEST(deleting_and_reading_non_exist_key);
  RUN_TEST(see_empty_slots_after_deleting);
  RUN_TEST(mini_fuzzy_testing);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();

  RUN_SUITE(special_cases);

  GREATEST_MAIN_END();

  return 0;
}
