/*
  This benchmarking was carried out by PerformanC, and it is not permitted to sell this code as a standalone product.

  Please note that this code does not follow the same license as TableC and is not a part of TableC. It is only intended for use in benchmarking the library.
  For any commercial use, please contact PerformanC directly.
*/

#include <stdio.h>
#include <time.h>
#include "../tablec.h"

#define MAX_EXECUTE 1
#define ADD_TIMES 1000000

char *Benchmarking[] = { "TableC Closed-addressing", "TableC Open-addressing" };

double firstBench() {
  clock_t startTime = clock();

  struct hashtable tablec;
  tablec_init(&tablec, ADD_TIMES, 1);

  char key[100];
  char *value = "Benchmarking";

  double i = 0;
  while (i <= ADD_TIMES) {
    snprintf(key, sizeof(key), "%f", i);
    tablec_set(&tablec, key, value);
    char *abc = tablec_get(&tablec, key);
    tablec_del(&tablec, key);
    i++;
  }

  tablec_cleanup(&tablec);

  return ((double)(clock() - startTime) / CLOCKS_PER_SEC);
}

int main() {
  double executedTimes = 0;
  double addedTime = 0;

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

  return 0;
}