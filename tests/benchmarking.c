/*
  This benchmarking was carried out by PerformanC, and it is not permitted to sell this code as a standalone product.

  Please note that this code does not follow the same license as TableC and is not a part of TableC. It is only intended for use in benchmarking the library.
  For any commercial use, please contact PerformanC directly.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

#include "../tablec.h"

#define MAX_EXECUTE 1000
#define ADD_TIMES 10000

char *Benchmarking[] = { "TableC No-Malloc" };

double firstBench(void) {
  clock_t startTime = clock();

  char key[100];
  char *value = "Benchmarking";
  double i = 0;

  struct tablec_oac_ht tablec;
  struct tablec_oac_bucket buckets[ADD_TIMES];
  tablec_oac_init(&tablec, buckets, ADD_TIMES);

  while (i++ <= ADD_TIMES) {
    sprintf(key, "%d", rand() % 1000);
    tablec_oac_set(&tablec, key, value, NULL);
    tablec_oac_get(&tablec, key, NULL);
    tablec_oac_del(&tablec, key, NULL);
  }

  return ((double)(clock() - startTime) / CLOCKS_PER_SEC);
}

int main(void) {
  double executedTimes = 0, addedTime = 0;

  firstBenchGoto:

  addedTime += firstBench();

  executedTimes++;

  if (executedTimes >= MAX_EXECUTE) {
    printf(
      "BENCHMARK FOR: %s\n"
      "EXECUTION TIME FOR FIRST BENCH:\n"
      "TIME TAKEN -> %f (%d times executed)\n"
      " SAMPLES   -> %d\n",
      Benchmarking[0], addedTime / MAX_EXECUTE, ADD_TIMES, MAX_EXECUTE);
  } else {
    goto firstBenchGoto;
  }

  executedTimes = 0, addedTime = 0;

  /* goto firstBenchGoto; */

  return 0;
}
