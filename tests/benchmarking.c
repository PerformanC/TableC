/*
  This benchmarking was carried out by PerformanC, and it is not permitted to sell this code as a standalone product.

  Please note that this code does not follow the same license as TableC and is not a part of TableC. It is only intended for use in benchmarking the library.
  For any commercial use, please contact PerformanC directly.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../tablec.h"

#define MAX_EXECUTE 1000
#define ADD_TIMES 10000

char *Benchmarking[] = { "TableC No-Malloc" };

double firstBench(void) {
  clock_t startTime = clock();

  char key[100];
  char *value = "Benchmarking";
  double i = 0;

  struct tablec_oanm_ht tablec;
  struct tablec_oanm_bucket buckets[ADD_TIMES];
  tablec_oanm_init(&tablec, buckets, ADD_TIMES);

  while (i++ <= ADD_TIMES) {
    sprintf(key, "%d", rand() % 1000);
    tablec_oanm_set(&tablec, key, value);
    tablec_oanm_get(&tablec, key);
    tablec_oanm_del(&tablec, key);
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
